#include "CustomScrollbar.h"

CustomScrollbar::CustomScrollbar(int width, QWidget *parent) : QScrollBar(parent)
{
    if (width == 0)
    {
        setStyleSheet("QScrollBar:vertical { \
                      border: none; \
                      background: rgba(255,255,255,0);\
                  }\
                  QScrollBar::handle:vertical{\
                      background-color: rgba(255,255,255,0);\
                      min-height: 20px;\
                  }\
                  QScrollBar::add-line:vertical {\
                      border: none;\
                      image: url(images/file_manager/file_management_dirlist_seek_down.bmp)\
                  }\
                  QScrollBar::sub-line:vertical {\
                      border: none;\
                      background-color: rgba(255,255,255,0);\
                      image: url(images/file_manager/file_management_dirlist_seek_up.bmp)\
                  }\
                  QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\
                      background: none;\
                  }\
                  ");
    }
    else
    {
                  setStyleSheet(QString("QScrollBar:vertical { \
                                border: none; \
                                background: rgba(255,255,255,0);\
                                width : %0;\
                            }\
                            QScrollBar::handle:vertical{\
                                background-color: rgba(255,255,255,0);\
                                min-height: 20px;\
                            }\
                            QScrollBar::add-line:vertical {\
                                border: none;\
                                image: url(images/file_manager/file_management_dirlist_seek_down.bmp)\
                            }\
                            QScrollBar::sub-line:vertical {\
                                border: none;\
                                background-color: rgba(255,255,255,0);\
                                image: url(images/file_manager/file_management_dirlist_seek_up.bmp)\
                            }\
                            QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\
                                background: none;\
                            }\
                            ").arg(width));

    }
}
