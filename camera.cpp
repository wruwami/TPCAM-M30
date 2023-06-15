/**
 * 
 **/

#include <QApplication>

#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraViewfinderSettings>
#include <QCameraInfo>
#include <QMediaMetaData>
#include <QVideoSurfaceFormat>

#include <QtWidgets>
#include <QMessageBox>
#include <QPalette>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>

#include "camera.h"

#include <thread>
#include <chrono>
#include <QCoreApplication>


#define FONT_SIZE 				12

#define QCAMERA_IMAGE_MODE	    "Image Mode"
#define QCAMERA_VIDEO_MODE		"Video Mode"

#define DIR_USERDATA			QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/Pictures"
#define DIR_HOME				QStandardPaths::writableLocation(QStandardPaths::HomeLocation)

#define SHM_NAME	QString("/tmp/shm")
#define SHM_DEV		QString("/dev/video1")

Q_DECLARE_METATYPE(QCameraInfo)

void thread_CommandExcute(QString strCommand)
{
	int result = std::system(strCommand.toStdString().c_str());

	qDebug() << strCommand << " : " << result;
}

Camera::Camera(QWidget *parent) :
    QGraphicsView(parent)
{
	QCameraInfo defaultCamera;

	m_dataLock.reset(new QMutex());

    cameraMode = QCAMERA_IMAGE_MODE;
	defaultCamera = initlayout();

	QFileInfo fi(DIR_USERDATA);
	if (fi.isDir()) {
		locationDir = DIR_USERDATA;
	} else {
		QFileInfo fi(DIR_HOME);
		if (fi.isDir()) {
			locationDir = DIR_HOME;
		}
	}

	imageCnt = videoCnt = 0;

	qDebug() << "Default camera : " << defaultCamera.deviceName() << ":" << defaultCamera.description();

	setCamera(defaultCamera);

	if (!setShmsink(SHM_NAME, SHM_DEV))
	{
		qDebug() << "gst shared memory sink start failed.";
	}
}

Camera::~Camera()
{
	//m_pProcess.waitForFinished();
	m_pProcess->close();
	delete m_pProcess;
	m_pProcess = nullptr;
}

QCameraInfo Camera::initlayout()
{
//    QFont font;
	QCameraInfo defaultCamInfo;
	bool findDefault = false;

//	QBoxLayout *vLayoutView = new QVBoxLayout();
//	QBoxLayout *vLayoutMenu = new QVBoxLayout();

//	font.setPixelSize(FONT_SIZE);

	const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();

	if (availableCameras.count() > 0) {
		defaultCamInfo = availableCameras[1];

	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("No camera is available."));
		QMetaObject::invokeMethod(this, "close", Qt::QueuedConnection);
	}

	// stacked 0: viewfinder
//	viewfinder = new QGraphicsView(this);
    this->setScene(new QGraphicsScene(this));
	pixmap = new QGraphicsPixmapItem();
	pixmap->setTransformationMode(Qt::FastTransformation);
    this->scene()->addItem(pixmap);

//	QGridLayout* layoutViewfinder = new QGridLayout();
//	layoutViewfinder->setMargin(0);
//	layoutViewfinder->addWidget(viewfinder);

//	QWidget* viewfinderPage = new QWidget();
//	viewfinderPage->setLayout(layoutViewfinder);

	// stacked 1: preview

//	QGridLayout* layoutPreview = new QGridLayout();
//	layoutPreview->setMargin(0);
//	layoutPreview->addWidget(previewLabel);

//	QWidget* previewPage = new QWidget();
//	previewPage->setLayout(layoutPreview);

	// stacking: viewfinder + preview
//	stackedWidget = new QStackedWidget();
//	stackedWidget->addWidget(viewfinderPage);
//	stackedWidget->addWidget(previewPage);

//	vLayoutView->addWidget(stackedWidget);
//	vLayoutView->addWidget(statusMessage);

//	vLayoutMenu->addWidget(softTrigButton);
//	vLayoutMenu->addWidget(exitButton);
//	vLayoutMenu->setAlignment(Qt::AlignTop);


//	QBoxLayout *hLayout = new QHBoxLayout;
//	hLayout->setMargin(0);
//	hLayout->addLayout(vLayoutView);
//	hLayout->addLayout(vLayoutMenu);

//	QWidget *widget = new QWidget;
//	widget->setLayout(hLayout);

//	setCentralWidget(widget);
	// setWindowState(Qt::WindowMaximized);
//	setWindowFlags(Qt::FramelessWindowHint);

	return defaultCamInfo;
}

void Camera::updateFrame(cv::Mat *mat)
{
	QTime sw;

	sw.start();

	m_dataLock->lock();
	currentFrame = *mat;
	m_dataLock->unlock();

	QImage qimg(currentFrame.data,
					currentFrame.cols,
					currentFrame.rows,
					currentFrame.step,
					QImage::Format_RGB888);

	pixmap->setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
    this->fitInView(pixmap, Qt::KeepAspectRatio);
}

void Camera::updateFPS(float fps)
{
	qDebug() << "FPS: " << fps;
}

bool Camera::setShmsink(QString qstrShmName, QString qstrDevice)
{
	m_pProcess = new QProcess;
	QString strShmsinkCommand = "gst-launch-1.0 rkisp device=" + qstrDevice + " io-mode=1 ! video/x-raw,format=NV12,width=1920,height=1080,framerate=30/1 ! videoconvert ! shmsink socket-path=/tmp/foo name=" + qstrShmName + " sync=false wait-for-connection=false shm-size=20000000";
	bool bGstShmsink = m_pProcess->startDetached(strShmsinkCommand);
	return bGstShmsink;
}

void Camera::setViewerToShmsrc(QString qstrShmName, int nFramerate, int nViewerWidth, int nViewerHeight)
{
	QString qstrViewerCommand = QString("shmsrc do-timestamp=true socket-path=/tmp/foo name=%1 ! video/x-raw,format=NV12,width=1920,height=1080,framerate=%2/1 ! queue ! videoscale ! video/x-raw,format=NV12,width=%3,height=%4 ! videoconvert ! appsink").arg(qstrShmName, QString::number(nFramerate), QString::number(nViewerWidth), QString::number(nViewerHeight));
	m_capturer.reset(new CaptureThread(QString(qstrViewerCommand), m_dataLock.data()));
}

QString Camera::GetFileName(bool bVideo, int idx, QString qstrDateTime, int nSpeed, int nSpeedLimit, int nCaptureSpeed, int nCaptureDistance
	, int nEnforcementRange, float fLatitude, float fLongitude, QString qstrLocation, QString qstrUsername, QString qstrDeviceID)
{
	QString qstrHead, qstrFileExtension;
	if (bVideo)
	{
		qstrHead = "AV";
		qstrFileExtension = "avi";
	}
	else
	{
		qstrHead = "AI";
		qstrFileExtension = "jpg";
	}

	QString qstrFilename;
	qstrFilename.sprintf("%s_%05d_%s_P%04d_%04d_%04d_%04d_NIN%02d_N%.6f_E%.6f_%s_%s_%s_S.%s"
		, qstrHead.toStdString().c_str()
		, idx
		, qstrDateTime.toStdString().c_str()
		, nSpeed
		, nSpeedLimit
		, nCaptureSpeed
		, nCaptureDistance
		, nEnforcementRange
		, fLatitude
		, fLongitude
		, qstrLocation.toStdString().c_str()
		, qstrUsername.toStdString().c_str()
		, qstrDeviceID.toStdString().c_str()
		, qstrFileExtension.toStdString().c_str()
	);

	return qstrFilename;
}
void Camera::saveVideoUseShmsrc(QString qstrVideoFilename, QString qstrPath, QString qstrEnfoceInfo, QString qstrShmName, bool bTimestamp, bool bTextoverlay, int nRecodeTime, int nFramerate, int nVideoWidth, int nVideoHeight)
{
	if (qstrPath != "")
	{
		mkDirs(qstrPath);
	}

	int nNumBuffer = nRecodeTime * nFramerate;
	QString qstrTimestamp = (bTimestamp) ? "! clockoverlay valignment=bottom halignment=left font-desc=\"Sans, 12\" time-format=\"%F %X\"" : "";
	QString qstrTextoverlay = "";
	if (bTextoverlay)
	{
		qstrTextoverlay.sprintf("! textoverlay text=\"%s\" valignment=bottom halignment=right font-desc=\"Sans, 12\"", qstrEnfoceInfo.toStdString().c_str());
	}

	QString strCommand = QString("gst-launch-1.0 shmsrc num-buffers=%1 do-timestamp=true socket-path=/tmp/foo name=%2 ! video/x-raw,format=NV12,width=%3,height=%4,framerate=%5/1 %6 %7 ! videoconvert ! jpegenc ! queue ! mux. alsasrc num-buffers=1024 ! audioconvert ! \'audio/x-raw,rate=44100,channels=2\' ! queue ! mux. avimux name=mux ! filesink location=%8%9"
		).arg(QString::number(nNumBuffer), qstrShmName, QString::number(nVideoWidth), QString::number(nVideoHeight), QString::number(nFramerate), qstrTimestamp, qstrTextoverlay, qstrPath, qstrVideoFilename);
	
	std::thread thread_command(thread_CommandExcute, strCommand);
	thread_command.detach();
}

void Camera::mkDirs(QString dir_path)
{
	QDir dir(dir_path);

	if (!dir.exists())
	{
		dir.mkpath(".");
	}

	QFile::Permissions permissions = QFile::ReadUser | QFile::WriteUser | QFile::ExeUser |
		QFile::ReadGroup | QFile::WriteGroup | QFile::ExeGroup |
		QFile::ReadOther | QFile::WriteOther | QFile::ExeOther;
	QFile::setPermissions(dir_path, permissions);
}

QString Camera::getTime()
{
	const auto now = std::chrono::system_clock::now();
	time_t tm_now = std::chrono::system_clock::to_time_t(now);
	struct tm tstruct = *localtime(&tm_now);

	struct tm tt;
	
	auto duration = now.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;

	QString qstrTime;
	qstrTime.sprintf("%04d%02d%02d_%02d%02d%02d%d"
		, tstruct.tm_year + 1900
		, tstruct.tm_mon + 1
		, tstruct.tm_mday
		, tstruct.tm_hour
		, tstruct.tm_min
		, tstruct.tm_sec
		, int(millis.count() / 100)
	);
	return qstrTime;
}

void Camera::setCamera(const QCameraInfo &cameraInfo)
{
	if (m_capturer) {
		if (m_capturer->isRunning())
			m_capturer->exit();
	}

	setViewerToShmsrc(SHM_NAME);
	if (m_capturer) {
		m_capturer->setRunning(false);
		disconnect(m_capturer.data(), &CaptureThread::frameCaptured, this, &Camera::updateFrame);
		connect(m_capturer.data(), &CaptureThread::finished, m_capturer.data(), &CaptureThread::deleteLater);
	}

	connect(m_capturer.data(), &CaptureThread::frameCaptured, this, &Camera::updateFrame);
	connect(m_capturer.data(), &CaptureThread::fpsChanged, this, &Camera::updateFPS);

	m_capturer->start();
	m_capturer->enableFPS(true);

//	displayViewfinder();
}

void Camera::configureCaptureSettings()
{
}

void Camera::updateRecordTime()
{
}

void Camera::record()
{
    QFileInfo fi;
    QString lo;

    lo = locationDir + "/" + "VIDEO" + QString::number(videoCnt) + ".avi";
    fi = QFileInfo(lo);

    while(fi.isFile()){
        videoCnt++;
        lo = locationDir + "/" + "VIDEO" + QString::number(videoCnt) + ".avi";
        fi = QFileInfo(lo);
    }

    vid.open(lo.trimmed().toStdString(), cv::VideoWriter::fourcc('M','J','P','G'), 30, cv::Size(1920, 1080),true);
    m_recordVideo = true;
}

void Camera::stop()
{
    m_recordVideo = false;
    vid.release();
}

//void Camera::displayViewfinder()
//{
//	stackedWidget->setCurrentIndex(0);
//	viewfinder->show();
//}

//void Camera::displayCapturedImage()
//{
//	stackedWidget->setCurrentIndex(1);
//}

void Camera::takeImage()
{
	qDebug() << locationDir;

	QFileInfo fi;
	QString lo;

	lo = locationDir + "/" + "PIC" + QString::number(imageCnt) + ".jpg";
	fi = QFileInfo(lo);

	while(fi.isFile()){
        imageCnt++;
		lo = locationDir + "/" + "PIC" + QString::number(imageCnt) + ".jpg";
		fi = QFileInfo(lo);
	}

	qDebug() << "Save image in : " << lo;

    m_imageFilename = lo;
    m_captureImage = true;

}


void Camera::processCapturedImage(int id, const QImage& img)
{
	Q_UNUSED(id);

//	qDebug() << "Viewfinder Size: " << viewfinder->size().width() << "x" << viewfinder->size().height();

    QImage scaledImage = img.scaled(this->size(),
									Qt::KeepAspectRatio,
									Qt::SmoothTransformation);


	qDebug() << "Viewfinder Size: " << scaledImage.width() << "x" << scaledImage.height();

//    previewLabel->setPixmap(QPixmap::fromImage(scaledImage.rgbSwapped()));

	// Display captured image for 4 seconds.
//	displayCapturedImage();

//	QTimer::singleShot(4000, this, &Camera::displayViewfinder);
}

void Camera::imageSaved(int id, const QString &fileName)
{
	Q_UNUSED(id);

	qDebug() << "Captured in : " << QDir::toNativeSeparators(fileName);

	m_isCapturingImage = false;
	if (m_applicationExiting)
		close();
}


void Camera::closeEvent(QCloseEvent *event)
{
	if (m_isCapturingImage) {
		setEnabled(false);
		m_applicationExiting = true;
		event->ignore();
	} else {
		event->accept();
	}

}


void Camera::onSoftTrigClicked()
{
	int idx = 1;
	int nSpeed = 66;
	int nSpeedLimit = 10;
	int nCaptureSpeed = 10;
	int nCaptureDistance = 88;
	int nEnfocementRange = 2;
	float fLatitude = 37.3552f;
	float fLongitude = 126.9661f;
	QString qstrLocation = "Loc1";
	QString qstrUsername = "User1";
	QString qstrDeviceID = "M0000P";

	QString qstrCurTime = getTime();
	qDebug() << "Current Time : " << qstrCurTime;
	QString qstrFilename = GetFileName(true, idx, qstrCurTime, nSpeed, nSpeedLimit, nCaptureSpeed, nCaptureDistance, nEnfocementRange, fLatitude, fLongitude, qstrLocation, qstrUsername, qstrDeviceID);
	qDebug() << "Filename : " << qstrFilename;

	QString qstrDatetimeDir = "/" + qstrCurTime.left(8) + "/" + qstrCurTime.left(11) + "/";
	QString qstrPath = QCoreApplication::applicationDirPath() + qstrDatetimeDir;
	qDebug() << "Path : " << qstrPath;

	QString qstrEnforceInfo;
	qstrEnforceInfo.sprintf("[%05d]C   %dkm/h,   %dm", idx, nSpeed, nCaptureDistance);

	saveVideoUseShmsrc(qstrFilename, qstrPath, qstrEnforceInfo, SHM_NAME, true, true, 10, 30, 1920, 1080);

}

int Camera::commandExcute(QString strCommand)
{
	return std::system(strCommand.toStdString().c_str());
}

void Camera::onExitClicked()
{
	m_capturer->setRunning(false);
	disconnect(m_capturer.data(), &CaptureThread::frameCaptured, this, &Camera::updateFrame);
	connect(m_capturer.data(), &CaptureThread::finished, m_capturer.data(), &CaptureThread::deleteLater);
	qApp->exit(0);
}
