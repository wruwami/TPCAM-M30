/**
 * 
 **/

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <QDebug>
#include <QScopedPointer>
#include <QMutex>
#include <QCameraInfo>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QImage>
// #include <QCamera>
// #include <QCameraViewfinder>
// #include <QCameraImageCapture>
// #include <QMediaRecorder>
#include <QStackedWidget>
#include <QLabel>
#include <QTimer>
#include <QProcess>

#include "opencv2/opencv.hpp"

#include "capture_thread.h"
#include "v4l2_thread.h"
#include "FileManager.h"

#define	RAW_IMAGE_WIDTH 1920
#define RAW_IMAGE_HEIGHT 1080
#define VIDEO_IMAGE_WIDTH 800
#define VIDEO_IMAGE_HEIGHT 480

enum EnforcementSaveType{
    Image,
    All,
    Video,
};

class Camera : public QGraphicsView
{
	Q_OBJECT

public:
    explicit Camera(QWidget *parent = nullptr);
    virtual ~Camera();

	QCameraInfo initlayout();

	int commandExcute(QString strCommand);

//	bool setShmsink(QString qstrShmName, QString qstrDevice);
	void setViewerToShmsrc(QString qstrShmName = "/tmp/shm", int nFramerate = 30, int nViewerWidth = 800, int nViewerHeight = 480);
//    QString GetFileName(bool bVideo, int idx, QString strDateTime, int nSpeed = 0, int nSpeedLimit = 0, int nCaptureSpeed = 0, int nCaptureDistance = 0, int nEnforcementRange = 0, float fLatitude = 0.f, float fLongitude = 0.f, QString strLocation = "Loc1", QString strUsername = "User", QString strDeviceID = "M0000P");
//    void saveVideoUseShmsrc(QString qstrVideoFilename, QString qstrPath = "", QString shmName = "/tmp/shm", int nRecodeTime = 10, int nFramerate = 30, int nVideoWidth = 1920, int nVideoHeight = 1080);
//	void mkDirs(QString dir_path);
	QString getTime();
    void SaveVideo(PrefixType, stEnforcementInfo, SDPath);
    void SaveImage(PrefixType, stEnforcementInfo, SDPath);
//    void SaveImage(PrefixType, stEnforcementInfo);

	
protected:
	void closeEvent(QCloseEvent *event) override;

private slots:
	void updateFrame(cv::Mat *mat);
	void updateFPS(float fps);
	
	void setCamera(const QCameraInfo &cameraInfo);
	void configureCaptureSettings();
	void record();
	void stop();

	void takeImage();

//	void displayViewfinder();
//	void displayCapturedImage();

	void processCapturedImage(int requestId, const QImage& img);
	void imageSaved(int id, const QString &fileName);

	// void displayCaptureError(int, QCameraImageCapture::Error, const QString &errorString);
	// void displayRecorderError();
    // void displayCameraError()stop;

	void updateRecordTime();

	// void updateCameraState(QCamera::State);
	// void updateRecorderState(QMediaRecorder::State state);

	/*void onCameraSwitch();
	void onCaptureModeSwitch();
	void onCaptureClicked();
	void onExitClicked();*/

    void onExitClicked();

	

private:
#if 0
	QCameraViewfinder   *viewfinder;
#else
//    QGraphicsView       *viewfinder;
	QGraphicsPixmapItem *pixmap;
#endif

	int imageCnt;
	int videoCnt;

	QString cameraMode;
	QString locationDir;

#if 1
	QScopedPointer<CaptureThread> m_capturer;
	QScopedPointer<QMutex> m_dataLock;

	QScopedPointer<v4l2_thread> m_v4l2Capturer;

	cv::Mat currentFrame;
    cv::VideoWriter vid;
#endif

	// QScopedPointer<QCamera> m_camera;
	// QScopedPointer<QCameraImageCapture> m_imageCapture;
	// QScopedPointer<QMediaRecorder> m_mediaRecorder;

	// QImageEncoderSettings m_imageSettings;
	// QVideoEncoderSettings m_videoSettings;
	// QAudioEncoderSettings m_audioSettings;

	QString m_videoContainerFormat;

    QString m_imageFilename;
    bool m_captureImage = false;
    QString m_videoFilename;
    bool m_recordVideo = false;

	bool m_isCapturingImage = false;
	bool m_applicationExiting = false;

	QProcess* m_pProcess;
	QString m_qstrCurTime;
    QPoint m_crossPos;
//protected:
//    void paintEvent(QPaintEvent *event);
};

#endif  /* __CAMERA_H__ */
