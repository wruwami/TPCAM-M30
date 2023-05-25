#include "RemoteControlWorker.h"

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "FileManager.h"

#include "MainWindow.h"
#include <QApplication>

static const char *const ev_value[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};


RemoteControlWorker::RemoteControlWorker(MainWindow* mainwindow, QObject *parent)
    : QObject{parent}
{
    m_pMainwindow = mainwindow;

}

RemoteControlWorker::~RemoteControlWorker()
{
//    qDebug() << Q_FUNC_INFO;
}

void RemoteControlWorker::doWork() {

    const char *ir_dev = "/dev/input/event0";
    struct input_event ev;

    ssize_t n;
    int fd;

    fd = open(ir_dev, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "can't open %s\n", ir_dev);
        return;
    }

    while (1) {
        n = read(fd, &ev, sizeof(ev));
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
        if (n != sizeof ev) {
            errno = EIO;
            break;
        }

        if (ev.type == EV_KEY && ev.value == 0)
        {
            switch (ev.code)
            {
            case 0x200: // 0
            {
//                QRect geometry;
//                for (QScreen *const screen : QGuiApplication::screens()) {
//                    geometry = geometry.united(screen->geometry());
//                }

//                QPixmap pixmap(QApplication::primaryScreen()->grabWindow(
//                              QApplication::desktop()->winId(),
//                              geometry.x(),
//                              geometry.y(),
//                              geometry.width(),
//                              geometry.height()
//                    ));
//                pixmap.setDevicePixelRatio(QApplication::desktop()->devicePixelRatio());
//                QString filename = GetSubPath("manual_capture", SD) + "/" + GetFile("SC");
//                pixmap.save(filename, 0, 100);

            }
                break;

            case 0x201: // 1
            {
            }
                break;
            case 0x202: // 2
            {
            }
                break;
            case 0x203: // 3
            {
                emit FirstAction();
                //m_pMainwindow->OpenEnforcement();
            }
                break;
            case 0x204: // 4
            {
            }
                break;
            case 0x205: // 5
            {
                m_pMainwindow->OpenFileManagement();
            }
                break;
            case 0x206: // 6
            {
            }
                break;
            case 0x207: // 7
            {
            }
                break;
            case 0x208: // 8
            {
            }
                break;
            case 0x209: // 9
            {
                char buff[256];
                memset(buff, 0, 256);
                FILE* fp = popen("pidof ffmpeg", "r");
                if (fp == NULL)
                {
                    perror("erro : ");
                    return;
                }

                while(fgets(buff, 256, fp) != NULL)
                {
                    printf("%s", buff);
                }

                if (!strlen(buff))
                {
                    QString cmd;
                    QString resolution = "800x480";
                    QString file_name = GetSubPath("manual_capture", SD) + "/" + GetFile("SR");
                    cmd = QString("ffmpeg -hwaccel opencl -y -f x11grab -framerate 10 -video_size %1 -i :0.0+0,0 -c:v libx264 -pix_fmt yuv420p -qp 0 -preset ultrafast %2 &").arg(resolution).arg(file_name);
                    system(cmd.toStdString().c_str());
                }
                else
                {
                    system("ps -ef | grep ffmpeg | awk '{print $2}' | xargs kill -9");
                }
            }
                break;
            case 0x20a: // *
            {
            }
                break;
            case 0x20b: // #
            {
            }
                break;

            }

            fprintf(stdout, "%s 0x%04x (%d)\n", ev_value[ev.value], (int)ev.code, (int)ev.code);
        }


    }

    close(fd);

    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));

    emit resultReady("end");
}

void RemoteControlWorker::doFirstAction()
{
    m_pMainwindow->OpenEnforcement();
}
