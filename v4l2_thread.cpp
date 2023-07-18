#include "v4l2_thread.h"

#define DEV_NAME "/dev/video0"
#define INFO_WIDTH 1920
#define INFO_HEIGHT 120
#define INFO_SPEED_WIDTH 320

#define IMAGE_ACQUISITION_FRAME_NUM 3

#define COLOR_YELLOW	cv::Scalar(100,240,240)
#define COLOR_RED		cv::Scalar(75,75,255)
#define COLOR_BLUE		cv::Scalar(255,75,75)
#define COLOR_WHITE		cv::Scalar(255,255,255)

cv::Mat g_matTargetCross;
cv::Mat g_matEnfoceInfo;
std::deque<stImgInfo> g_dqYuvImgInfo;
std::deque<stImgDataInfo> g_dqYuvImgDataInfo;
std::mutex g_mutexImgBuf;
bool g_bSave = true;
bool g_bTargetCross = true;

#define DEBUG_MODE 1

static void thread_CopyImage(struct buffer* buff, int size, stEnforceInfo enforceInfo)
{
	try
	{
		stImgDataInfo imgDataInfo;
		imgDataInfo.enforceInfo = enforceInfo;
		//imgDataInfo.pImg = new unsigned char[size];
		memcpy(imgDataInfo.pImg, buff->start, size);
		//DBG("No.%d copied\n", count);
		/*if (DEBUG_MODE)
			qDebug() << "No." << count << "copied";*/

		g_mutexImgBuf.lock();
		g_dqYuvImgDataInfo.push_back(imgDataInfo);
		g_mutexImgBuf.unlock();
	}
	catch (std::exception& e)
	{
		//DBG("exception : %s\n", e.what());
		//if(DEBUG_MODE)
		qDebug() << "exception : " << e.what();
	}
}

cv::Mat getEnfoceInfoImage(stEnforceInfo& enforceInfo)
{
	cv::Mat matInfo = g_matEnfoceInfo.clone();

	cv::String strText;

	strText = cv::format("DT:%s", enforceInfo.qstrDatetime.toStdString().c_str());
	cv::putText(matInfo, strText, cv::Point(15, INFO_HEIGHT/2 - 15), cv::FONT_HERSHEY_COMPLEX, 1.2, COLOR_WHITE, 2);

	strText = cv::format("DID:%s", enforceInfo.qstrDeviceID.toStdString().c_str());
	cv::putText(matInfo, strText, cv::Point(720, INFO_HEIGHT / 2 - 15), cv::FONT_HERSHEY_COMPLEX, 1.2, COLOR_WHITE, 2);

	strText = cv::format("UN:%s", enforceInfo.qstrUsername.toStdString().c_str());
	cv::putText(matInfo, strText, cv::Point(1030, INFO_HEIGHT / 2 - 15), cv::FONT_HERSHEY_COMPLEX, 1.2, COLOR_WHITE, 2);

	strText = cv::format("SL:%dkm/h", enforceInfo.nSpeedLimit);
	cv::putText(matInfo, strText, cv::Point(1300, INFO_HEIGHT / 2 - 15), cv::FONT_HERSHEY_COMPLEX, 1.2, COLOR_WHITE, 2);

	strText = cv::format("Loc:%s", enforceInfo.qstrLocation.toStdString().c_str());
	cv::putText(matInfo, strText, cv::Point(15, INFO_HEIGHT - 20), cv::FONT_HERSHEY_COMPLEX, 1.2, COLOR_WHITE, 2);

	strText = cv::format("CD:%dm", enforceInfo.nCaptureDistance);
	cv::putText(matInfo, strText, cv::Point(1300, INFO_HEIGHT - 20), cv::FONT_HERSHEY_COMPLEX, 1.2, COLOR_WHITE, 2);

	strText = cv::format("%dkm/h", enforceInfo.nSpeed);
	cv::putText(matInfo, strText, cv::Point(1630, INFO_HEIGHT - 40), cv::FONT_HERSHEY_COMPLEX, 1.6, COLOR_WHITE, 3);
	/*cv::putText();
	cv::putText();
	cv::putText();
	cv::putText();
	cv::putText();*/

	return matInfo.clone();
}

static void thread_SaveImgFunc()
{
	size_t nSize = 0;
	cv::Mat matYuv(cv::Size(IMAGE_WIDTH, IMAGE_HEIGHT * 3 / 2), CV_8UC1);
	cv::Mat rgbmat(cv::Size(IMAGE_WIDTH, IMAGE_HEIGHT), CV_8UC3);

	while (g_bSave)
	{
		try
		{
			nSize = g_dqYuvImgDataInfo.size();
			if (nSize > 0)
			{
				g_mutexImgBuf.lock();
				stImgDataInfo imgInfo = g_dqYuvImgDataInfo.front();
				g_dqYuvImgDataInfo.pop_front();
				g_mutexImgBuf.unlock();

				memcpy(matYuv.data, imgInfo.pImg, 1920 * 1620);
				cv::cvtColor(matYuv, rgbmat, cv::COLOR_YUV2BGR_NV12);

				cv::vconcat(getEnfoceInfoImage(imgInfo.enforceInfo), rgbmat, rgbmat);

				if (g_bTargetCross)
				{
					cv::Rect rcROI;
					rcROI.x = imgInfo.enforceInfo.nTargetCrossX - g_matTargetCross.cols / 2;
					rcROI.y = imgInfo.enforceInfo.nTargetCrossY - g_matTargetCross.rows / 2 + INFO_HEIGHT;
					rcROI.width = g_matTargetCross.cols;
					rcROI.height = g_matTargetCross.rows;

					if (rcROI.x < 0)	rcROI.x = 0;
					if (rcROI.y < 0)	rcROI.y = 0;
					if (rcROI.x + rcROI.width >= rgbmat.cols)	rcROI.x = rgbmat.cols - rcROI.width - 1;
					if (rcROI.y + rcROI.height >= rgbmat.rows)	rcROI.x = rgbmat.rows - rcROI.height - 1;

					cv::Mat matImgROI(rgbmat, rcROI);
					cv::addWeighted(matImgROI, 1.0, g_matTargetCross, 0.50, 0.0, matImgROI);
				}
				cv::imwrite(imgInfo.enforceInfo.qstrFullPath.toStdString().c_str(), rgbmat);

				//qDebug() << "saved image";
			}
		}
		catch (std::exception& e)
		{
			//DBG("exception : %s\n", e.what());
			//if(DEBUG_MODE)
			qDebug() << "exception : " << e.what();
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	//qDebug() << "saved image thread exit";
}

v4l2_thread::v4l2_thread()
    : running(false)
	, m_bDeviceValid(false)
	, m_nFrameCnt(0)
{
    QString targetFile = "images/enforcement/target.jpg";
    g_matTargetCross = cv::imread(targetFile.toStdString(), cv::IMREAD_COLOR);
	cv::resize(g_matTargetCross, g_matTargetCross, cv::Size(80,80));

    cv::hconcat(cv::Mat(INFO_HEIGHT, INFO_WIDTH - INFO_SPEED_WIDTH, CV_8UC3, cv::Scalar(16, 16, 16)), cv::Mat(INFO_HEIGHT, INFO_SPEED_WIDTH, CV_8UC3, cv::Scalar(0, 0, 104)), g_matEnfoceInfo);
	//cv::imwrite("InfoImg.jpg", g_matEnfoceInfo);

	std::thread _t1(thread_SaveImgFunc);
	_t1.detach();
}

v4l2_thread::~v4l2_thread()
{
    g_bSave = false;
}

void v4l2_thread::setRunning(bool run)
{
    if (!run)
        g_bSave = false;

    running = run;
}

void v4l2_thread::run()
{
    unsigned int count = 1;
    unsigned long read_start_time, read_end_time, ms;
    float fps = 0;

	running = true;

    while (running)
    {
		//qDebug() << "m_bDeviceValid : " << m_bDeviceValid;
		if (m_bDeviceValid)
		{
			try
			{
				/*if (DEBUG_MODE)
					qDebug() << "No." << count;*/
				//DBG("No.%d\n", count);        //Display the current image frame number

				if (m_stEnforceInfo.bImageSave)
				{
					if (m_bUseFlash)
					{
						if (m_nFrameCnt == IMAGE_ACQUISITION_FRAME_NUM)
						{
							//qDebug() << "flash on";
							//flash on
							setFlash(true);
						}
						else if (m_nFrameCnt == IMAGE_ACQUISITION_FRAME_NUM - 1)
						{
							//qDebug() << "flash off";
							//flash off
							setFlash(false);
						}
					}
					//frame num countdown
					--m_nFrameCnt;
				}				

				read_start_time = get_time();
				read_frame(count);
				read_end_time = get_time();

				ms = read_end_time - read_start_time;
				fps = (1.f / (float)ms) * 1000;

				/*if (DEBUG_MODE)
					qDebug() << "take time " << read_end_time - read_start_time << "ms, " << int(fps);*/
				//DBG("take time %lu ms, %0.0f fps\n", read_end_time - read_start_time, fps);
				++count;
			}
			catch (std::exception& e)
			{
				qDebug() << "exception : " << e.what();
				m_bDeviceValid = false;
			}
		}
    }
	if (DEBUG_MODE)
		qDebug() << "READ AND SAVE DONE!";
    //DBG("\nREAD AND SAVE DONE!\n");
}

void v4l2_thread::imageGrab(QString qstrFullPath, QString qstrDatetime, QString qstrDeviceID, QString qstrUsername, QString qstrLocation, int nSpeedLimit, int nCaptureDistance, int nSpeed, int nTargetCrossX, int nTargetCrossY)
{
	if (m_nFrameCnt > 0)
	{
		if (DEBUG_MODE)
			qDebug() << "image grab signal ignored because image grab is still in progress.";

		return;
	}
	else
		qDebug() << "imag grab signal recv";
		
	m_stEnforceInfo.bImageSave = true;
	m_stEnforceInfo.qstrFullPath = qstrFullPath;
	m_stEnforceInfo.qstrDatetime = qstrDatetime;
	m_stEnforceInfo.qstrDeviceID = qstrDeviceID;
	m_stEnforceInfo.qstrUsername = qstrUsername;
	m_stEnforceInfo.qstrLocation = qstrLocation;
	m_stEnforceInfo.nSpeedLimit = nSpeedLimit;
	m_stEnforceInfo.nCaptureDistance = nCaptureDistance;
	m_stEnforceInfo.nSpeed = nSpeed;
	m_stEnforceInfo.nTargetCrossX = nTargetCrossX;
	m_stEnforceInfo.nTargetCrossY = nTargetCrossY;

	m_nFrameCnt = IMAGE_ACQUISITION_FRAME_NUM;
}

void v4l2_thread::initV4l2(int w, int h)
{
	m_bDeviceValid = true;
    fd = -1;
    fp = NULL;
    silent = 0;
    width = w;
    height = h;
    buf_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format = V4L2_PIX_FMT_NV12;

	//m_stEnforceInfo = stEnforceInfo();
	m_nFrameCnt = 0;

    g_dqYuvImgInfo.clear();
    g_dqYuvImgDataInfo.clear();

	m_bUseFlash = true;

    open_device();
    init_device();
    start_capturing();
}

void v4l2_thread::setUseFlash(bool bUseFlash)
{
	m_bUseFlash = bUseFlash;
}
void v4l2_thread::setUseTargetCross(bool bTargetCross)
{
	g_bTargetCross = bTargetCross;
}

void v4l2_thread::errno_exit(const char* s)
{
    qDebug() << s << "error " << errno << ", " << strerror(errno);
    m_bDeviceValid = false; //
    /*ERR("%s error %d, %s\n", s, errno, strerror(errno));
    exit(EXIT_FAILURE);*/
}
int v4l2_thread::xioctl(int fh, int request, void *arg)
{
    int r;
    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);
    return r;
}
void v4l2_thread::open_device(void)
{
    fd = open(DEV_NAME, O_RDWR /* required */ /*| O_NONBLOCK*/, 0);

    if (-1 == fd) {
		qDebug() << "Cannot open" << DEV_NAME << " : " << errno << ", " << strerror(errno);
		//ERR("Cannot open '%s': %d, %s\n", DEV_NAME, errno, strerror(errno));
        m_bDeviceValid = false; //exit(EXIT_FAILURE);
    }
}
void v4l2_thread::setFlash(bool bFlash)
{
	/*if(bFlash)
		system("echo firefly | echo 1 > /sys/class/leds/green/user/brightness");
	else
		system("echo firefly | echo 0 > /sys/class/leds/green/user/brightness");*/

	QFile file("/sys/class/gpio/gpio154/value");
	if (bFlash)
	{
		file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
		file.write("1");
	}
	else
	{
		file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
		file.write("0");
	}
	file.close();
}
void v4l2_thread::init_mmap(void)
{
    struct v4l2_requestbuffers req;

    CLEAR(req);

    req.count = BUFFER_COUNT;
    req.type = buf_type;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            qDebug() << DEV_NAME << " does not support memory mapping";
            //ERR("%s does not support memory mapping\n", DEV_NAME);
            m_bDeviceValid = false; //exit(EXIT_FAILURE);
            return;
        }
        else {
            errno_exit("VIDIOC_REQBUFS");
        }
    }

    if (req.count < 2) {
        qDebug() << "Insufficient buffer memory on " << DEV_NAME;
        //ERR("Insufficient buffer memory on %s\n", DEV_NAME);
        m_bDeviceValid = false; //exit(EXIT_FAILURE);
        return;
    }

    buffers = (struct buffer*)calloc(req.count, sizeof(*buffers));

    if (!buffers) {
        qDebug() << "Out of memory";
        //ERR("Out of memory\n");
        m_bDeviceValid = false; //exit(EXIT_FAILURE);
        return;
    }

    for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
        struct v4l2_buffer buf;
        struct v4l2_plane planes[FMT_NUM_PLANES];
        CLEAR(buf);
        CLEAR(planes);

        buf.type = buf_type;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;

        if (V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE == buf_type) {
            buf.m.planes = planes;
            buf.length = FMT_NUM_PLANES;
        }

        if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
            errno_exit("VIDIOC_QUERYBUF");

        if (V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE == buf_type) {
            buffers[n_buffers].length = buf.m.planes[0].length;
            buffers[n_buffers].start =
                mmap(NULL /* start anywhere */,
                    buf.m.planes[0].length,
                    PROT_READ | PROT_WRITE /* required */,
                    MAP_SHARED /* recommended */,
                    fd, buf.m.planes[0].m.mem_offset);
        }
        else {
            buffers[n_buffers].length = buf.length;
            buffers[n_buffers].start =
                mmap(NULL /* start anywhere */,
                    buf.length,
                    PROT_READ | PROT_WRITE /* required */,
                    MAP_SHARED /* recommended */,
                    fd, buf.m.offset);
        }

        if (MAP_FAILED == buffers[n_buffers].start)
            errno_exit("mmap");
    }
}
void v4l2_thread::init_device(void)
{
    struct v4l2_capability cap;
    struct v4l2_format fmt;

    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) {
        if (EINVAL == errno) {
            qDebug() << DEV_NAME << " is no V4L2 device";
            //ERR("%s is no V4L2 device\n", DEV_NAME);
            m_bDeviceValid = false; //exit(EXIT_FAILURE);
            return;
        }
        else {
            errno_exit("VIDIOC_QUERYCAP");
        }
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) &&
        !(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE_MPLANE)) {
        qDebug() << DEV_NAME << "  is not a video capture device, capabilities: " <<  std::hex << cap.capabilities;
        //ERR("%s is not a video capture device, capabilities: %x\n", DEV_NAME, cap.capabilities);
        m_bDeviceValid = false; //exit(EXIT_FAILURE);
        return;
    }

    if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
        qDebug() << DEV_NAME << "  does not support streaming i/o";
        //ERR("%s does not support streaming i/o\n", DEV_NAME);
        m_bDeviceValid = false; //exit(EXIT_FAILURE);
        return;
    }

    if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)
        buf_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    else if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE_MPLANE)
        buf_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;

    CLEAR(fmt);
    fmt.type = buf_type;
    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
    fmt.fmt.pix.pixelformat = format;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

    if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
        errno_exit("VIDIOC_S_FMT");

    init_mmap();
}
void v4l2_thread::start_capturing(void)
{
    unsigned int i;
    enum v4l2_buf_type type;

    for (i = 0; i < n_buffers; ++i) {
        struct v4l2_buffer buf;

        CLEAR(buf);
        buf.type = buf_type;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE == buf_type) {
            struct v4l2_plane planes[FMT_NUM_PLANES];

            buf.m.planes = planes;
            buf.length = FMT_NUM_PLANES;
        }
        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
            errno_exit("VIDIOC_QBUF");
    }
    type = buf_type;
    if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
        errno_exit("VIDIOC_STREAMON");
}

int v4l2_thread::read_frame(int count)
{
    struct v4l2_buffer buf;
    int i, bytesused;

    CLEAR(buf);

    buf.type = buf_type;
    buf.memory = V4L2_MEMORY_MMAP;

    if (V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE == buf_type) {
        struct v4l2_plane planes[FMT_NUM_PLANES];
        buf.m.planes = planes;
        buf.length = FMT_NUM_PLANES;
    }

    if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf))
        errno_exit("VIDIOC_DQBUF");

    i = buf.index;

    if (V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE == buf_type)
        bytesused = buf.m.planes[0].bytesused;
    else
        bytesused = buf.bytesused;

  
	if (m_stEnforceInfo.bImageSave && m_nFrameCnt == 0)
	{
		//qDebug() << "SaveImage start";
		std::thread thread0(thread_CopyImage, &(buffers[i]), bytesused, m_stEnforceInfo);
		thread0.detach();

		m_stEnforceInfo.bImageSave = false;
	}

	/*if (DEBUG_MODE)
		qDebug() << "bytesused " <<  bytesused;*/
    //DBG("bytesused %d\n", bytesused);

    if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
        errno_exit("VIDIOC_QBUF");   

    return 1;
}
unsigned long v4l2_thread::get_time(void)
{
    struct timeval ts;
    gettimeofday(&ts, NULL);
    return (ts.tv_sec * 1000 + ts.tv_usec / 1000);
}
