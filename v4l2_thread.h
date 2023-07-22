#ifndef V4L2_THREAD_H
#define V4L2_THREAD_H

#include <QScopedPointer>
#include <QThread>
#include <QMutex>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QFile>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h> /* getopt_long() */
#include <fcntl.h> /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <dlfcn.h>

#include <deque>
#include <mutex>
#include <thread>
#include <chrono>

#include "opencv2/opencv.hpp"

#include <linux/videodev2.h>

#define BUFFER_COUNT 4
#define FMT_NUM_PLANES 1
#define CLEAR(x) memset(&(x), 0, sizeof(x))

//#define DBG(...) do { if(!silent) printf(__VA_ARGS__); } while(0)
//#define ERR(...) do { fprintf(stderr, __VA_ARGS__); } while (0)

#define IMAGE_WIDTH 1920
#define IMAGE_HEIGHT 1080

typedef struct _ST_ENFORCE_INFO
{
    bool	bImageSave;
    QString qstrFullPath;
    QString qstrDatetime;
    QString qstrDeviceID;
    QString qstrUsername;
    QString qstrLocation;
    int		nSpeedLimit;
    int		nCaptureDistance;
    int		nSpeed;
    int		nTargetCrossX;
    int		nTargetCrossY;
    /*_ST_ENFORCE_INFO()
    {
        this->bImageSave = false;
        this->qstrFullPath = "";
        this->qstrDatetime = "";
        this->qstrDeviceID = "";
        this->qstrUsername = "";
        this->qstrLocation = "";
        this->nSpeedLimit = 0;
        this->nCaptureDistance = 0;
        this->nSpeed = nSpeed;
    }*/
    void operator=(_ST_ENFORCE_INFO& enforceInfo)
    {
        this->bImageSave = enforceInfo.bImageSave;
        this->qstrFullPath = enforceInfo.qstrFullPath;
        this->qstrDatetime = enforceInfo.qstrDatetime;
        this->qstrDeviceID = enforceInfo.qstrDeviceID;
        this->qstrUsername = enforceInfo.qstrUsername;
        this->qstrLocation = enforceInfo.qstrLocation;
        this->nSpeedLimit = enforceInfo.nSpeedLimit;
        this->nCaptureDistance = enforceInfo.nCaptureDistance;
        this->nSpeed = enforceInfo.nSpeed;
        this->nTargetCrossX = enforceInfo.nTargetCrossX;
        this->nTargetCrossY = enforceInfo.nTargetCrossY;
    }
}stEnforceInfo;

struct buffer
{
    void *start;
    size_t length;
    struct v4l2_buffer v4l2_buf;
};

typedef struct _ST_IMG_INFO
{
    cv::Mat matImg;
    std::string strTime;
	//stEnforceInfo enforceInfo;
}stImgInfo;

typedef struct _ST_IMG_DATA_INFO
{
    unsigned char pImg[IMAGE_WIDTH* 1080*3/2];
	stEnforceInfo enforceInfo;
}stImgDataInfo;

class v4l2_thread : public QThread
{
public:
    v4l2_thread();
    ~v4l2_thread() override;

    void setRunning(bool run);

private:
	bool running;

private:
    int fd;// = -1;
    FILE *fp;// = NULL;
    unsigned int n_buffers;
    buffer *buffers;
    int silent;// = 0;

    //char dev_name[255];
    int width;
    int height;
    enum v4l2_buf_type buf_type;// = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int format;// = V4L2_PIX_FMT_NV12;

    bool m_bDeviceValid;
    //bool m_bImageSave;
	stEnforceInfo m_stEnforceInfo;
	int m_nFrameCnt;  

	int m_bUseFlash;

public:
    void initV4l2(int w = IMAGE_WIDTH, int h = IMAGE_HEIGHT);
    void errno_exit(const char* s);
    int xioctl(int fh, int request, void *arg);
    void open_device(void);
    void setFlash(bool bFlash);
    void init_mmap(void);
    void init_device(void);
    void start_capturing(void);
    //void process_buffer(struct buffer* buff, int size, std::string strTime);
    int read_frame(int count);
    unsigned long get_time(void);
    //cv::Mat getEnfoceInfoImage(stEnforceInfo& enforceInfo);
	void imageGrab(QString qstrFullPath, QString qstrDatetime, QString qstrDeviceID, QString qstrUsername, QString qstrLocation, int nSpeedLimit, int nCaptureDistance, int nSpeed, int nTargetCrossX, int nTargetCrossY);

	void setUseFlash(bool bUseFlash);
	void setUseTargetCross(bool bTargetCross);

public:
    bool isDeviceValid(void) { return m_bDeviceValid; }

protected:
    void run() override;
};

#endif // V4L2_THREAD_H
