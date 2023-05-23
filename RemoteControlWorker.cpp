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

#include "MainWindow.h"

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
                m_pMainwindow->OpenEnforcement();
            }
                break;
            case 0x204: // 4
            {
            }
                break;
            case 0x205: // 5
            {
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
