#ifndef __CAPTURETHREAD_H__
#define __CAPTURETHREAD_H__

#include <QScopedPointer>
#include <QThread>
#include <QMutex>
#include <QString>
#include <QTimer>

#include "opencv2/opencv.hpp"

class CaptureThread : public QThread
{
	Q_OBJECT

public:
	CaptureThread(int id, QMutex *lock);
	CaptureThread(QString videoPath, QMutex *lock);
	~CaptureThread() override;

	void setRunning(bool run) { running = run; }
	void enableFPS(bool enable);

private slots:
	void updateFPS();

private:
	bool running;

	int cameraId;
	QString videoPath;

	QMutex *data_lock;

	cv::VideoCapture cap;

	cv::Mat frame;
	int frames;

	QScopedPointer<QTimer> fpsTimer;
	bool enable_fps;
	float fps;

protected:
	void run() override;

signals:
	void frameCaptured(cv::Mat *data);
	void fpsChanged(float fps);
};

#endif /* __CAPTURETHREAD_H__ */
