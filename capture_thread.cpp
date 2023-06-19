/**
 * 
 **/

#include <QDebug>
#include <QMutex>
#include <QString>
#include <QTime>

#include "opencv2/opencv.hpp"

#include "capture_thread.h"

CaptureThread::CaptureThread(int id, QMutex *lock):
	running(false), cameraId(id), videoPath(""), data_lock(lock), enable_fps(false)
{
	frames = 0;
	fps = 0.0;
}

CaptureThread::CaptureThread(QString videoPath, QMutex *lock):
	running(false), cameraId(-1), videoPath(videoPath), data_lock(lock), enable_fps(false)
{
	frames = 0;
	fps = 0.0;
}

CaptureThread::~CaptureThread() {
	running = false;
}

void CaptureThread::run() {
	QTime sw;
	running = true;

	if (cap.isOpened()) {
		cap.release();
	}

	if (cameraId == -1) {
		cap.open(videoPath.trimmed().toStdString(), cv::CAP_GSTREAMER);
    }
	else {
		cap.open(cameraId, cv::CAP_GSTREAMER);
	}

	cv::Mat tmp_frame;

	while (running) {
		sw.restart();
		cap >> tmp_frame;
		if (!tmp_frame.empty()) {
			if (enable_fps)
				frames++;

			// cvtColor(tmp_frame, tmp_frame, cv::COLOR_BGR2RGB);
			data_lock->lock();
			frame = tmp_frame;
            data_lock->unlock();

			emit frameCaptured(&frame);
			// qDebug() << "1 frame in " << sw.elapsed() << " ms";

		}
	}

	if (cap.isOpened()) {
		cap.release();
	}

	running = false;
}

void CaptureThread::enableFPS(bool enable)
{
	if (enable) {
		if (enable_fps) return;
		fpsTimer.reset(new QTimer());
        connect(fpsTimer.data(), SIGNAL(timeout()), this, SLOT(updateFPS()));
		fpsTimer->start(1000);
	}
	else {
		if (!enable_fps) return;
		fpsTimer.reset();
	}

	enable_fps = enable;
}

void CaptureThread::updateFPS()
{
	fps = frames / 1.0; //1000.0 is 1sec
	frames = 0;

	// emit fpsChanged(fps);
#if 0
	qDebug() << "FPS:: " << fps;
#endif
}
