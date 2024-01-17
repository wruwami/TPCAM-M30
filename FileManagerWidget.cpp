#include "FileManagerWidget.h"
#include "ui_FileManagerWidget.h"

#include "qdir.h"
#include "qdiriterator.h"
#include <QDebug>
#include <QPainter>
#include <QHeaderView>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QByteArray>
#include <QBuffer>
#include <QAbstractTableModel>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QAbstractVideoBuffer>

#include "CustomPushButton.h"
#include "StringLoader.h"
#include "BaseDialog.h"
#include "FileManagerSnapShotDialog.h"
#include "WidgetSize.h"
#include "KeypadDialog.h"
#include "StillImageViewerDialog.h"
#include "MovieViewerDialog.h"
#include "MovieViewerDialogSub.h"
#include "FileManagerFileTransferDialog.h"
//#include "FileManagerFileTransferWidget.h"
#include "SearchBoxDialog.h"
#include "thermal_printer.h"
#include "FileManager.h"
#include "ImageConverter.h"
#include "WidgetSize.h"
#include "SpeedUnitManager.h"
#include "Logger.h"
#include "ConfigManager.h"
#include "DateFormatManager.h"
#include "QtAVPlayer/qavplayer.h"
#include "QtAVPlayerHelper/videowidget.h"
#include "Print.h"

enum Mode
{
    I_MODE,
    A_MODE,
    V_MODE,
    M_MODE,
    S_MODE,
};

bool TimeLessThan(const AVFileFormat& s1, const AVFileFormat& s2)
{
    return atoi(s1.time) < atoi(s2.time);
}

ST_ENFORCEMENT_FILENAME_ELEMENT g_file_elem_for_printer;
char g_print_img_body_buff_file_management[1712 * 984];  // Only Y among YUV 420 image body buffer for thermal printer from uncompressed jpg file
char g_print_img_body_buff_file_logo[1712 * 984];  // David, Add for LOGO file


FileManagerWidget::FileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerWidget)
{
    ui->setupUi(this);

    ui->ImageVideoComboBox->addItem(LoadString("IDS_I"));
    ui->ImageVideoComboBox->addItem(LoadString("IDS_A"));
    ui->ImageVideoComboBox->addItem(LoadString("IDS_V"));
    ui->ImageVideoComboBox->addItem(LoadString("IDS_MANUAL_CAPTURE"));
    ui->ImageVideoComboBox->addItem(LoadString("IDS_SCREEN"));

    ui->dateImageLabel->setImage("file_manager", "file_management_folder_icon_small.bmp");
    ui->datePushButton->setText(LoadString("IDS_DATE"));
    ui->datePushButton->setFontSize(23);
    ui->datePushButton->setStyleSheet("QPushButton {background-color: rgba(255,255,255,0); border:none;}");

    ui->firstPushButton->setImage("file_manager", "file_management_prev_big_seek_button.bmp");
    ui->previousPushButton->setImage("file_manager", "file_management_prev_seek_button.bmp");
    ui->nextPushButton->setImage("file_manager", "file_management_next_seek_button.bmp");
    ui->lastPushButton->setImage("file_manager", "file_management_next_big_seek_button.bmp");

//    ui->firstPushButton->setStyleSheet(QString("image: url(images/file_manager/file_management_prev_big_seek_button.png); width: %0; height : %1;").arg(ui->firstPushButton->width(), ui->firstPushButton->height()));
    ui->percentPushButton->setDisabled(true);
    ui->percentPushButton->setText("S:0%");
    ui->percentPushButton->setFontSize(23);
    ui->connectPushButton->setText(LoadString("IDS_CONNECT"));
    ui->connectPushButton->setFontSize(23);

    QJsonObject object = ConfigManager("parameter_setting4.json").GetConfig();
    if(object["printer items"].toArray()[object["printer selection"].toInt()-1].toString() == "IDS_A4")
        ui->connectPushButton->setEnabled(false);
    else
        ui->connectPushButton->setEnabled(true);

    ui->printPushButton->setText(LoadString("IDS_PRINT"));
    ui->printPushButton->setFontSize(23);
    ui->printPushButton->setDisabled(true);

    ui->mainMenuPushButton->setImage("file_manager", "file_management_home.jpg");
    ui->searchPushButton->setImage("file_manager", "file_management_search.jpg");
    ui->zoomPlayPushButton->setImage("file_manager", "file_management_zoom.png");
    ui->deletePushButton->setImage("file_manager", "file_management_delete_all.jpg");
    ui->sharePushButton->setImage("file_manager", "file_management_ftp.jpg");
    ui->movePushButton->setImage("file_manager", "file_management_copy_usb.jpg");
    ui->datePushButton->setFontSize(23);

    ui->tableWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setStyleSheet("QTableWidget::item {border : none;}");
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);

//    ui->tableWidget->setSectionResizeMode(0, QHeaderView.Stretch);

//    ui->horizontalLayout_9->setMargin(GetWidthWidth(15));
//    ui->horizontalLayout_9->setSpacing(GetWidthWidth(30));

    m_pHomePushButton = ui->mainMenuPushButton;

    ui->frameLabel->setText(LoadString("IDS_STILL_IMAGE_AND_MOVIE_VIEWER"));
//    ui->frameLabel->setFontSize(23);
//    m_videoWidget\\ = new QVideoWidget;
//    ui->verticalLayout->insertWidget(1, m_videoWidget, 335);
////    m_videoWidget->setGeometry(ui->frameLabel->geometry());
//    m_videoWidget->hide();
//    m_pVideoWidget = new VideoWidget;
    //    ui->verticalLayout->insertWidget(1, m_videoWidget, 335);
    ////    m_videoWidget->setGeometry(ui->frameLabel->geometry());
    //    m_videoWidget->hide();

    m_player = new QAVPlayer(this);
//    m_player->setVideoOutput(m_pVideoWidget);

//    CreateWiFiReadThreadAndInitPrinter();

////    QRect rect = ui->gridLayout_2->contentsRect();
//    int width = ((getScreenWidth() - 15) / 21 * 9);//ui->percentPushButton->width() + ui->connectPushButton->width() + ui->printPushButton->width();
////    int width = ui->horizontalLayout->itemAt(0)->geometry().width();

    QHeaderView *verticalHeader = ui->tableWidget->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    object = ConfigManager("parameter_setting4.json").GetConfig();
    if (object["printer selection"].toInt() == 2)
    {

        m_bA4Print = true;
        SetPrintEnabled();
        ui->printPushButton->setDisabled(false);
    }

    QObject::connect(m_player, &QAVPlayer::videoFrame, [&](const QAVVideoFrame &frame) {
        // QAVVideoFrame is comppatible with QVideoFrame
        QAVVideoFrame::MapData mapData = frame.map();
        {
            QVideoFrame videoFrame = frame.convertTo(AV_PIX_FMT_RGB32);
            if(videoFrame.map(QAbstractVideoBuffer::ReadOnly))
            {
                QPixmap pixmap;
                QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat());
                m_image = QImage( videoFrame.bits(),
                            videoFrame.width(),
                            videoFrame.height(),
                            videoFrame.bytesPerLine(),
                            imageFormat);
        //        QImage image = videoFrame.image();
        //        pixmap.fromImage(videoFrame.image().scaled(ui->frameLabel->size(), Qt::IgnoreAspectRatio, Qt::FastTransformation));
                ui->frameLabel->setImage(QPixmap::fromImage(m_image).scaled(ui->frameLabel->size(), Qt::IgnoreAspectRatio, Qt::FastTransformation));

                // QAVVideoFrame can be converted to various pixel formats
        //        auto convertedFrame = frame.convert(AV_PIX_FMT_YUV420P);

                // Easy getting data from video frame
        //        auto mapped = videoFrame.map(); // downloads data if it is in GPU
        //        qDebug() << mapped.format << mapped.size;

                // The frame might contain OpenGL or MTL textures, for copy-free rendering
        //        qDebug() << frame.handleType() << frame.handle();
            }
        }
    });

////    int width = ui->tableWidget->width();//kui->gridLayout_2->itemAtPosition(1, 0)->geometry().width();

////    verticalHeader->setSectionResizeMode(0, QHeaderView::Stretch);
////    verticalHeader->setSectionResizeMode(1, QHeaderView::Stretch);
////    verticalHeader->resizeSection(0, width /3);
////    verticalHeader->resizeSection(1, width /3 * 2);
//    verticalHeader->setDefaultSectionSize(24);

//    QHeaderView *horizontalHeader = ui->tableWidget->horizontalHeader();
////    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch);
//    horizontalHeader->setSectionResizeMode(0, QHeaderView::Fixed);
//    horizontalHeader->setSectionResizeMode(1, QHeaderView::Fixed);
//int width = horizontalHeader->defaultSectionSize();

//    int width = ui->tableWidget->width();
//    horizontalHeader->resizeSection(0, width * 105 / (230 + 105));
//    horizontalHeader->resizeSection(1, width * 230 / (230 + 105));


    //    MyHeader* header = new MyHeader(Qt::Horizontal, ui->tableWidget);

//    ui->tableWidget->setHorizontalHeader(new ComboHeader);
//    QStyle::CE_CheckBox
//    header->setsty
//    ui->tableWidget->setHorizontalHeader(header);
//    ui->tableWidget->setGeometry(ui->gridLayout_2->itemAtPosition(1, 1)->geometry());
//    ui->tableWidget->setColumnWidth(0, ui->gridLayout_2->itemAtPosition(1, 1)->geometry().width());
//    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    connect(ui->tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(on_tableWidget_clicked(const QModelIndex&)));

//    ui->tableWidget->setStyleSheet("item { color:black; } item:selected { color:red; }");

    initTable();
    startTimer(1000);
}

FileManagerWidget::~FileManagerWidget()
{
    delete m_player;
//    delete m_videoWidget;
    delete ui;
}

void FileManagerWidget::setTableContent()
{
    ui->tableWidget->clear();
    int j = 0;

    if (m_avFileFormatList.size() == 0)
        return;
//    if (m_nMode != S_MODE)
//    {
    for (int i = m_AVFileFormatIndex ; i < m_AVFileFormatIndex + 5 ; i++, j++)
    {
        if (i >= m_avFileFormatList.size())
            break;
        AVFileFormat avfileFormat = m_avFileFormatList[i];
        QString index;
        index.sprintf("%05d", i+1);
        QTableWidgetItem* indexItem = new QTableWidgetItem(index);
        float nCaptureSpeed = getSpeedValue(avfileFormat.captureSpeed.mid(1,4).toFloat());
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(nCaptureSpeed, 'f', 0) + speedUnitValue() +", " + QString("%0%1:%2%3:%4%5").arg(avfileFormat.time[0]).arg(avfileFormat.time[1]).arg(avfileFormat.time[2]).arg(avfileFormat.time[3]).arg(avfileFormat.time[4]).arg(avfileFormat.time[5]));
        ui->tableWidget->setItem(j, 0, indexItem);
        ui->tableWidget->setItem(j, 1, item);
    }
//    }
//    else
//    {
//        for (int i = m_AVFileFormatIndex ; i < m_AVFileFormatIndex + 5 ; i++, j++)
//        {
//            if (i >= m_avFileFormatList.size())
//                break;
//            AVFileFormat avfileFormat = m_avFileFormatList[i];
//            QString index;
//            index.sprintf("%05d", i+1);
//            QTableWidgetItem* indexItem = new QTableWidgetItem(index);
//            QString date = QString(avfileFormat.date);
//            QTableWidgetItem* item = new QTableWidgetItem(date);
//            ui->tableWidget->setItem(j, 0, indexItem);
//            ui->tableWidget->setItem(j, 1, item);
//        }

//    }
}

void FileManagerWidget::resizeEvent(QResizeEvent *event)
{
    int width = (event->size().width() - 6 - 9 - 9) * 9 / 21;
    ui->tableWidget->setColumnWidth(0, width * 105 / (230 + 105));
    ui->tableWidget->setColumnWidth(1, width * 230 / (230 + 105));

    ui->frameLabel->resizeImage(ui->frameLabel->size());

//    ui->firstPushButton->setStyleSheet(QString("image: url(images/file_manager/file_management_prev_big_seek_button.png); width: %0, height : %1").arg(ui->firstPushButton->width(), ui->firstPushButton->height()));
}

void FileManagerWidget::paintEvent(QPaintEvent *event)
{
//    QWidget::paintEvent(event);
    QPainter painter(this);
    QStyleOptionFrame  option;
    option.initFrom(this);
    option.rect = ui->verticalLayout_2->geometry();
    option.lineWidth = 1;
    option.frameShape = QFrame::Box;
    style()->drawPrimitive(QStyle::PE_Frame,  &option,  &painter,  this);

    QStyleOptionFrame  option2;
    option2.initFrom(this);
    option2.rect = QRect(ui->horizontalLayout_7->geometry().left(), (ui->horizontalLayout_7->geometry().top() + ui->gridLayout_2->geometry().bottom()) / 2, ui->verticalLayout_2->geometry().width(), 1);
    option2.lineWidth = 1;
    option2.frameShape = QFrame::HLine;
    style()->drawPrimitive(QStyle::PE_Frame,  &option2,  &painter,  this);

    QStyleOptionFrame  option3;
    option3.initFrom(this);
    option3.rect = QRect(ui->horizontalLayout_7->geometry().left(), (ui->horizontalLayout_5->geometry().top() + ui->horizontalLayout_7->geometry().bottom()) / 2, ui->verticalLayout_2->geometry().width(), 1);
    option3.lineWidth = 1;
    option3.frameShape = QFrame::HLine;
    style()->drawPrimitive(QStyle::PE_Frame,  &option3,  &painter,  this);

    QPen Pen(Qt::black);
    Pen.setStyle(Qt::SolidLine);
    painter.setPen(Pen);
    painter.drawLine(ui->tableWidget->geometry().left() + ui->tableWidget->geometry().width() * 105 / (230 + 105), ui->dateImageLabel->geometry().top(), ui->tableWidget->geometry().left() + ui->tableWidget->size().width() * 105 / (230 + 105), ui->tableWidget->geometry().bottom());

}

void FileManagerWidget::timerEvent(QTimerEvent *event)
{
    float percent = 0;
    if (m_sdcardManager.GetSDAvailable() != 0 && m_sdcardManager.GetSDTotal() != 0)
        percent = 100 - (m_sdcardManager.GetSDAvailable() / m_sdcardManager.GetSDTotal() * 100);
    ui->percentPushButton->setText(QString("S:%1%").arg(QString::number(percent, 'f', 0)));
    ui->percentPushButton->setFontSize(23);
}

void FileManagerWidget::on_deletePushButton_clicked()
{
    SetLogMsg(FILE_MANAGER, "DELETE");

    BaseDialog baseDialog(Dialog::FileManagerQuestionMessageWidgetType, Qt::AlignmentFlag::AlignCenter, "");
    if (baseDialog.exec() == QDialog::Accepted)
    {
        BaseDialog baseDialog2(Dialog::AdminPWWidgetType, Qt::AlignmentFlag::AlignCenter, LoadString("IDS_PLEASE_INPUT_PW"));
        if (baseDialog2.exec() == QDialog::Accepted)
        {
            QDir dir(GetSDPath());
            dir.removeRecursively();
//            QDirIterator iterDir(GetSDPath(), QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
//            while (iterDir.hasNext())
//            {
//                iterDir.next();

//                QFile file(iterDir.filePath());
//                file.remove();
//            }
            ui->tableWidget->clear();
            ui->frameLabel->removeImage();
            m_avFileFormatList.clear();
//            m_currentAVFileFormat = nullptr;
        }

    }

}


void FileManagerWidget::convertValue()
{
    memcpy(g_file_elem_for_printer.prefix, m_currentAVFileFormat.filePrefix, 2 + 1);
    memcpy(g_file_elem_for_printer.file_id, m_currentAVFileFormat.index, 5 + 1);
    memcpy(g_file_elem_for_printer.year, &m_currentAVFileFormat.date[0], 4 + 1);
    g_file_elem_for_printer.year[4] = '\0';
    memcpy(g_file_elem_for_printer.month, &m_currentAVFileFormat.date[4], 2 + 1);
    g_file_elem_for_printer.month[2] = '\0';
    memcpy(g_file_elem_for_printer.day, &m_currentAVFileFormat.date[6], 2 + 1);
    g_file_elem_for_printer.day[2] = '\0';
    memcpy(g_file_elem_for_printer.hour, &m_currentAVFileFormat.time[0], 2 + 1);
    g_file_elem_for_printer.hour[2] = '\0';
    memcpy(g_file_elem_for_printer.minute, &m_currentAVFileFormat.time[2], 2 + 1);
    g_file_elem_for_printer.minute[2] = '\0';
    memcpy(g_file_elem_for_printer.second, &m_currentAVFileFormat.time[4], 2);
    g_file_elem_for_printer.second[2] = '\0';
    memcpy(g_file_elem_for_printer.msec, &m_currentAVFileFormat.time[6], 1 + 1);
    g_file_elem_for_printer.msec[1] = '\0';
    memcpy(g_file_elem_for_printer.laser_capture_speed, m_currentAVFileFormat.captureSpeed.toStdString().c_str(), 5 + 1);
    memcpy(g_file_elem_for_printer.display_limit_speed, m_currentAVFileFormat.speedLimit.toStdString().c_str(), 4 + 1);
    memcpy(g_file_elem_for_printer.capture_limit_speed, m_currentAVFileFormat.captureSpeedLimit.toStdString().c_str(), 4 + 1);
    memcpy(g_file_elem_for_printer.laser_capture_distance, m_currentAVFileFormat.distance.toStdString().c_str(), 4 + 1);
//    snprintf(g_file_elem_for_printer.user_mode, 1, m_currentAVFileFormat);
//    snprintf(g_file_elem_for_printer.enforcement_mode, 1, m_currentAVFileFormat);
//    snprintf(g_file_elem_for_printer.dual_mode, 1, m_currentAVFileFormat.);
//    snprintf(g_file_elem_for_printer.zoom_level, 2, m_currentAVFileFormat);
    memcpy(g_file_elem_for_printer.latitude, m_currentAVFileFormat.latitude.toStdString().c_str(), 10 + 1);
    memcpy(g_file_elem_for_printer.longitude, m_currentAVFileFormat.longitude.toStdString().c_str(), 11 + 1);
    g_file_elem_for_printer.location = m_currentAVFileFormat.location.toStdString();
    g_file_elem_for_printer.user_name = m_currentAVFileFormat.userId.toStdString();
    g_file_elem_for_printer.device_id = m_currentAVFileFormat.deviceId.toStdString();
//    memcpy(g_file_elem_for_printer.location, m_currentAVFileFormat.location.toStdString().c_str(), m_currentAVFileFormat.location.size());
//    memcpy(g_file_elem_for_printer.user_name, m_currentAVFileFormat.userId.toStdString().c_str(), m_currentAVFileFormat.userId.size());
//    memcpy(g_file_elem_for_printer.device_id, m_currentAVFileFormat.deviceId.toStdString().c_str(), m_currentAVFileFormat.deviceId.size());

//    char location[LOCATION_MAX_LENGTH];
//    memset(location, 0, LOCATION_MAX_LENGTH);
//    memcpy(location, m_currentAVFileFormat.userId.toStdString().c_str(), m_currentAVFileFormat.userId.size());
//    memcpy(g_file_elem_for_printer.user_name, m_currentAVFileFormat.userId.toStdStrin\g().c_str(), m_currentAVFileFormat.userId.size());
//    memcpy(g_file_elem_for_printer.device_id, m_currentAVFileFormat.deviceId.toStdString().c_str(), m_currentAVFileFormat.deviceId.size());
    memcpy(g_file_elem_for_printer.unit, &m_currentAVFileFormat.unit, 1 + 1);
//    g_file_elem_for_printer.unit[0] = &m_currentAVFileFormat.unit;

}

void FileManagerWidget::initTable()
{
    QString path = "/snapshot";
    QDirIterator iterDir(GetSDPath() + path, QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDirIterator::Subdirectories);
    QString pre_dir = "";
    while (iterDir.hasNext())
    {
        QString dir = iterDir.next();
        QStringList dirList = dir.split("/");
        QDir qdir(dir);
        QString dir2 = dirList[dirList.count() - 1];
        qdir.setFilter( QDir::AllEntries | QDir::NoDotAndDotDot );

        if (dir2.toUInt() > pre_dir.toUInt() && qdir.count() > 0)
        {
            pre_dir = dir2;
        }
    }

        m_dateTime = pre_dir;
//        int index = date.lastIndexOf('/');
//        m_dateTime = date.mid(index + 1, date.size() - index - 1);
        ui->datePushButton->setText(pre_dir);



        QString full_date_path = GetPath(path, SD) + "/" + pre_dir;

        ui->tableWidget->clear();
        m_avFileFormatList.clear();
        m_AVFileFormatIndex = 0;

        int i = 0;
        QDirIterator it(full_date_path, QDir::Files);
        while (it.hasNext())
        {
            QString file = it.next();
            int index = file.lastIndexOf('/');
//            if (file.mid(file.size() - 1, 1) == ".")
//                continue;
            //addListItem(file);

            AVFileFormat avfileFormat = GetFileFormat(file);
            if (!avfileFormat.file_path.contains(".lock"))
            {
                m_avFileFormatList.append(avfileFormat);
            }
            else
            {
                QFile file(avfileFormat.file_path);
                file.remove();
            }

        }
        std::sort(m_avFileFormatList.begin(), m_avFileFormatList.end(), TimeLessThan);
        m_avPreviousFileFormatList = m_avFileFormatList;

        if ((m_avFileFormatList.size() % 5) != 0)
            m_AVFileFormatIndex = m_avFileFormatList.size() - (m_avFileFormatList.size() % 5);
        else
            m_AVFileFormatIndex = m_avFileFormatList.size() - 5;

    setTableContent();

    int row = m_avFileFormatList.size() % 5 - 1;
     if (row == -1)
         row = 0;
     emit ui->tableWidget->cellClicked(row, 0);
    //    ui->tableWidget->cellClicked()
}

//void FileManagerWidget::printA4()
//{
//    QTextDocument doc;
////    doc.setTextWidth()
//    QTextCursor cursor(&doc);

//    QPixmap pixmap;
//    pixmap.load(GeteMMCPath() + "/" + "images" + "/" + "booting" + "/" + "comlaser_logo.bmp");
//    QImage logoImage = pixmap.toImage();

//    cursor.insertImage(logoImage);
//    QTextCharFormat textFormat;
//    textFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
//    QFont font = textFormat.font();
//    font.setPixelSize(15);
//    textFormat.setFont(font);


//    cursor.insertText(LoadString("IDS_POLICE_OVER_SPEEDING_TICKET"), textFormat);

////    QTextFrameFormat frameFormat;
////    frameFormat.setHeight(10);
////    frameFormat.setWidth(612);
////    QColor line = QColor(47, 104, 172);
////    frameFormat.setBackground(line);
////    cursor.insertFrame(frameFormat);
////    cursor.insert
//    pixmap.load(GeteMMCPath() + "/" + "images" + "/" + "booting" + "/" + "blueLine.png");
//    pixmap = pixmap.scaledToWidth(612, Qt::SmoothTransformation);
//    logoImage = pixmap.toImage();
//    cursor.insertImage(logoImage);

//    font.setPixelSize(15);
//    textFormat.setFont(font);

//    cursor.insertBlock();
//    cursor.insertBlock();
//    cursor.insertText(LoadString("IDS_DID") + " : " + m_currentAVFileFormat.deviceId, textFormat);
//    cursor.insertBlock();
//    cursor.insertBlock();
//    cursor.insertText(LoadString("IDS_UN") + " : " + m_currentAVFileFormat.userId, textFormat);
//    cursor.insertBlock();
//    cursor.insertBlock();
//    cursor.insertText(LoadString("IDS_DATE") + " : " + GetDate(QString(m_currentAVFileFormat.date).mid(0, 8)), textFormat);
//    cursor.insertBlock();
//    cursor.insertBlock();
//    QString time = QString(m_currentAVFileFormat.time).mid(0, 2) + ":" + QString(m_currentAVFileFormat.time).mid(2, 2) + ":" + QString(m_currentAVFileFormat.time).mid(4, 2);
//    cursor.insertText(LoadString("IDS_TIME") + " : " + time, textFormat);
//    cursor.insertBlock();
//    cursor.insertBlock();
//    QString speedUnit;
//    QString distanceUnit;
//    if (QString(m_currentAVFileFormat.unit) == "S")
//    {
//        speedUnit = "Km/h";
//        distanceUnit = "meter";
//    }
//    else
//    {
//        speedUnit = "mph";
//        distanceUnit = "feet";
//    }

//    cursor.insertText(LoadString("IDS_SPEED_LIMIT") + " : " + QString::number(m_currentAVFileFormat.speedLimit.toInt()) + " " + speedUnit, textFormat);
//    cursor.insertBlock();
//    cursor.insertBlock();
//    int captureSpeed;
//    if (m_currentAVFileFormat.captureSpeed.mid(0,1) == "M")
//    {
//        captureSpeed = -(m_currentAVFileFormat.captureSpeed.mid(1,4).toInt());
//    }
//    else
//    {
//        captureSpeed = (m_currentAVFileFormat.captureSpeed.mid(1,4).toInt());
//    }
//    cursor.insertText(LoadString("IDS_VIOLATION_SPEED") + " : "+ QString::number(captureSpeed) + " " + speedUnit, textFormat);
//    cursor.insertBlock();
//    cursor.insertBlock();
//    cursor.insertText(LoadString("IDS_RANGE") + " : " + QString::number(m_currentAVFileFormat.distance.toInt()) + " " + distanceUnit, textFormat);
//    cursor.insertBlock();
//    cursor.insertBlock();
//    cursor.insertText(LoadString("IDS_LOCATION") + " : " + m_currentAVFileFormat.location + "(" + m_currentAVFileFormat.latitude + "," + m_currentAVFileFormat.longitude + ")", textFormat);
//    cursor.insertBlock();
//    cursor.insertBlock();


//    QPixmap pixmap2;
//    pixmap2.load(m_currentAVFileFormat.file_path);
//    pixmap2 = pixmap2.scaled(612,344, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

//    QImage logoImage2 = pixmap2.toImage();
//    cursor.insertImage(logoImage2);
//    cursor.insertBlock();
//    cursor.insertBlock();

//    pixmap.load(GeteMMCPath() + "/" + "images" + "/" + "booting" + "/" + "blueLine.png");
//    pixmap = pixmap.scaledToWidth(612, Qt::SmoothTransformation);
//    logoImage = pixmap.toImage();
//    cursor.insertImage(logoImage);

////    cursor.insertFrame(frameFormat);

//    cursor.insertBlock();
//    cursor.insertText(LoadString("IDS_PRINT_DATE") + " : " + GetDate(QDate::currentDate().toString("yyyyMMdd")), textFormat);
//    cursor.insertBlock();
//    cursor.insertBlock();
//    cursor.insertText(LoadString("IDS_OFFIEC_ID") + " : ", textFormat);
//    textFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
//    cursor.insertText("                  ", textFormat);

//    textFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);

//    cursor.insertText("                  " + LoadString("IDS_SIGNATURE") + " : ", textFormat);
//    textFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
//    cursor.insertText("                  ", textFormat);


////    doc.setHtml();

//    QPrinter printer;
//    QPrintDialog dialog(&printer);
//    if (dialog.exec() == QDialog::Accepted)
//    {
//        doc.print(&printer);
//    }
//}

void FileManagerWidget::SetPrintEnabled()
{
    if (m_bA4Print)
    {
        ui->connectPushButton->setDisabled(true);
        ui->printPushButton->setDisabled(false);
    }
    else
    {
        ui->connectPushButton->setDisabled(false);
        ui->printPushButton->setDisabled(true);
    }
}

//void FileManagerWidget::on_tableWidget_clicked(const QModelIndex &index)
//{
//    if (m_avFileFormatList.size() >= (index.row() + m_AVFileFormatIndex))
//        m_currentAVFileFormat = m_avFileFormatList[index.row()+ m_AVFileFormatIndex];
//    else
//        return;

//    ui->tableWidget->item(index.row(), 0)->setTextColor(Qt::red);
//    ui->tableWidget->item(index.row(), 1)->setTextColor(Qt::red);
//    for (int i = 0 ; i < 5 ; i++)
//    {
//        if (index.row() != i)
//        {
//            ui->tableWidget->item(i, 0)->setTextColor(Qt::black);
//            ui->tableWidget->item(i, 1)->setTextColor(Qt::black);
//        }
//    }

//    convertValue();

//    if (!strncmp(m_currentAVFileFormat.filePrefix, "VV", 2))
//    {
//        m_videoWidget->show();
//        ui->frameLabel->hide();
//        m_player->setMedia(QUrl::fromLocalFile(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path));
//        m_player->play();
//        m_player->pause();
//    }
//    else if (!strncmp(m_currentAVFileFormat.filePrefix, "AV", 2))
//    {
//        m_videoWidget->show();
//        ui->frameLabel->hide();
//        m_player->setMedia(QUrl::fromLocalFile(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path));
//        m_player->play();
//        m_player->pause();
//    }
//    else if (!strncmp(m_currentAVFileFormat.filePrefix, "SR", 2))
//    {
//        m_videoWidget->show();
//        ui->frameLabel->hide();
//        m_player->setMedia(QUrl::fromLocalFile(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path));
//        m_player->play();
//        m_player->pause();
//    }
//    else if (!strncmp(m_currentAVFileFormat.filePrefix, "MV", 2))
//    {
//        m_videoWidget->show();
//        ui->frameLabel->hide();
//        m_player->setMedia(QUrl::fromLocalFile(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path));
//        m_player->play();
//        m_player->pause();
//    }
//    else if (!strncmp(m_currentAVFileFormat.filePrefix, "AI", 2))
//    {
//        ui->frameLabel->show();
//        m_videoWidget->hide();
//        ui->frameLabel->setImage(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path, ui->frameLabel->size());
//    }
//    else if (!strncmp(m_currentAVFileFormat.filePrefix, "SC", 2))
//    {
//        ui->frameLabel->show();
//        m_videoWidget->hide();
//        ui->frameLabel->setImage(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path, ui->frameLabel->size());
//    }
//}

void FileManagerWidget::on_searchPushButton_clicked()
{
//    QString title_text = m_currentAVFileFormat.date

    SearchBoxDialog searchBoxDialog(m_dateTime);
    if (searchBoxDialog.exec() == QDialog::Accepted)
    {
        int firstValue = searchBoxDialog.getFirstValue();
        int secondValue = searchBoxDialog.getSecondValue();
        QList<AVFileFormat> avFileFormatList;

        m_avFileFormatList = m_avPreviousFileFormatList;

        foreach (auto avFormat, m_avFileFormatList)
        {
            int minute = QString(avFormat.time).mid(2, 2).toInt();
            if ( minute >= firstValue && secondValue >= minute)
            {
                avFileFormatList.push_back(avFormat);
            }
        }
        m_avFileFormatList = avFileFormatList;
        m_AVFileFormatIndex = 0;
        setTableContent();
    }
    else
    {

    }
}

void FileManagerWidget::on_zoomPlayPushButton_clicked()
{
    if (m_avFileFormatList.size() == 0)
        return;

    if (!strncmp(m_currentAVFileFormat.filePrefix, "VV", 2))
    {
        MovieViewerDialogSub movieViewerDialogSub(m_currentAVFileFormat);
        movieViewerDialogSub.exec();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "AV", 2))
    {
        MovieViewerDialogSub movieViewerDialogSub(m_currentAVFileFormat);
        movieViewerDialogSub.exec();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "SR", 2))
    {
        MovieViewerDialogSub movieViewerDialogSub(m_currentAVFileFormat);
        movieViewerDialogSub.exec();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "MV", 2))
    {
        MovieViewerDialogSub movieViewerDialogSub(m_currentAVFileFormat);
        movieViewerDialogSub.exec();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "AI", 2))
    {
        StillImageViewerDialog stillImageViewDialog(m_currentAVFileFormat);
        stillImageViewDialog.exec();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "SC", 2))
    {
        StillImageViewerDialog stillImageViewDialog(m_currentAVFileFormat);
        stillImageViewDialog.exec();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "MC", 2))
    {
        StillImageViewerDialog stillImageViewDialog(m_currentAVFileFormat);
        stillImageViewDialog.exec();
    }
}

void FileManagerWidget::on_sharePushButton_clicked()
{
//    BaseDialog baseDialog(FileManagerFileTransferWidgetType, Qt::AlignmentFlag::AlignCenter, "", true, LoadString("IDS_FTP_FILE_TRANSFER"));
//    baseDialog.exec();
    SetLogMsg(FILE_MANAGER, "SHARE");

    ConfigManager config = ConfigManager("parameter_setting6.json");
    QJsonObject jsonObject = config.GetConfig();

    if (jsonObject["ftp select"].toInt() != 1)
    {
        FileManagerFileTransferDialog fileManagerFileTransferDialog(FTPType);
        fileManagerFileTransferDialog.exec();
    }

//    QEventLoop loop;
//    FileManagerFileTransferWidget fileManagerFileTransferWidget(FTPType);
//    fileManagerFileTransferWidget.show();
//    connect(&fileManagerFileTransferWidget, SIGNAL(finished()), &loop, SLOT(quit()));
//    loop.exec();
}

void FileManagerWidget::on_movePushButton_clicked()
{
    SetLogMsg(FILE_MANAGER, "MOVE");
//    BaseDialog baseDialog(FileManagerFileTransferWidgetType, Qt::AlignmentFlag::AlignCenter, "", true, LoadString("IDS_USB_MEMORY_TRANSFER"));
//    baseDialog.exec();

    if (!GetUSBPath().isEmpty())
    {
        FileManagerFileTransferDialog fileManagerFileTransferDialog(FileType);
        fileManagerFileTransferDialog.exec();
    }
//    QEventLoop loop;
//    FileManagerFileTransferWidget fileManagerFileTransferWidget(FileType);
//    fileManagerFileTransferWidget.show();
//    fileManagerFileTransferWidget.transFile
//    connect(&fileManagerFileTransferWidget, SIGNAL(finished()), &loop, SLOT(quit()));
//    loop.exec();

}

void FileManagerWidget::on_printPushButton_clicked()
{
//    QImage image(m_currentAVFileFormat.file_path);
//    image.convertToFormat(QImage::Format::Format_RGB32);

    if (m_bA4Print)
    {
        Print print(m_currentAVFileFormat, m_image);
    }
    else
    {
        ImageConverter imageConvert(ui->frameLabel->pixmap()->toImage());
        imageConvert.Convert();

        while(!connect_wifi_printer())
        {
            printf("connect_wifi_printer failed");
            usleep(100);
        }

        printf("connect_wifi_printer Done");

        sleep(1);

        // int number;
        // printf("\n");
        // scanf("%d", &number);

        // wait(number);

//        print_wifi_printer(NULL);
        print_wifi_printer();
    }

    SetLogMsg(FILE_MANAGER, "PRINT");
}

void FileManagerWidget::on_connectPushButton_clicked()
{

    if (!connect_wifi_printer())
    {
        BaseDialog baseDialog(FileManagerErrorMessageWidgetType, Qt::AlignmentFlag::AlignCenter);
        baseDialog.exec();
    }
    else
    {
        ui->printPushButton->setDisabled(false);
    }

    SetLogMsg(FILE_MANAGER, "CONNECT");
}

void FileManagerWidget::on_percentPushButton_clicked()
{

}

void FileManagerWidget::on_ImageVideoComboBox_currentIndexChanged(int index)
{
    ui->tableWidget->clear();
    ui->datePushButton->setText("");
    m_avFileFormatList.clear();
    m_AVFileFormatIndex = 0;

    switch (index)
    {
    case 0: // I
    {
        m_nMode = Mode::I_MODE;
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_zoom.png");
        SetPrintEnabled();
    }
        break;
    case 1: // A
    {
        m_nMode = Mode::A_MODE;
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_play.png");
        SetPrintEnabled();
    }
        break;
    case 2: // V
    {
        m_nMode = Mode::V_MODE;
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_play.png");
        SetPrintEnabled();
    }
        break;
    case 3: // M
    {
        m_nMode = Mode::M_MODE;
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_zoom.png");
        SetPrintEnabled();
    }
        break;
    case 4: // S
    {
        m_nMode = Mode::S_MODE;
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_zoom.png");
        ui->connectPushButton->setDisabled(true);
        ui->printPushButton->setDisabled(true);
    }
        break;
    }
}

void FileManagerWidget::on_datePushButton_clicked()
{
    FileManagerSnapShotDialog fileManagerSnapShotDialog(m_nMode);
    if (fileManagerSnapShotDialog.exec() == QDialog::Accepted)
    {
//        m_folder_path = fileManagerSnapShotDialog.strDate();
//        QDir dirfolder_path
        QString date = fileManagerSnapShotDialog.strDate();
        m_dateTime = date;
//        int index = date.lastIndexOf('/');
//        m_dateTime = date.mid(index + 1, date.size() - index - 1);
        ui->datePushButton->setText(date);
        ui->datePushButton->setFontSize(23);

        QString path;
        switch (m_nMode)
        {
        case I_MODE:
        {
            path = "/snapshot";
            break;
        }
        case A_MODE:
        {
            path = "/auto";
            break;
        }
        case V_MODE:
        {
            path = "/video";
            break;
        }
        case M_MODE:
        {
            path = "/manual_capture";
            break;
        }
        case S_MODE:
        {
            path = "/screen";
            break;
        }

        }

        QString full_date_path = GetPath(path, SD) + "/" + date;

        ui->tableWidget->clear();
        m_avFileFormatList.clear();
        m_AVFileFormatIndex = 0;

        int i = 0;
        QDirIterator it(full_date_path, QDir::Files);
        while (it.hasNext())
        {
            QString file = it.next();
            int index = file.lastIndexOf('/');
//            if (file.mid(file.size() - 1, 1) == ".")
//                continue;
            //addListItem(file);


            AVFileFormat avfileFormat = GetFileFormat(file);
            if (!avfileFormat.file_path.contains(".lock"))
            {
                m_avFileFormatList.append(avfileFormat);
            }
            else
            {
                QFile file(avfileFormat.file_path);
                file.remove();
            }

//            m_avFileFormatList.append(avfileFormat);

//            QTableWidgetItem* indexItem = new QTableWidgetItem(QString::number(i + 1));

//            QTableWidgetItem* item = new QTableWidgetItem(getSpeedValue(avfileFormat.captureSpeed.toFloat()) + speedUnitValue()+", " + QString("%0%1:%2%3:%4%5").arg(avfileFormat.time[0]).arg(avfileFormat.time[1]).arg(avfileFormat.time[2]).arg(avfileFormat.time[3]).arg(avfileFormat.time[4]).arg(avfileFormat.time[5]));
//            if (i < 6)
//            {
//                ui->tableWidget->setItem(i, 0, indexItem);
//                ui->tableWidget->setItem(i++, 1, item);
//            }
        }
        std::sort(m_avFileFormatList.begin(), m_avFileFormatList.end(), TimeLessThan);
        m_avPreviousFileFormatList = m_avFileFormatList;

        setTableContent();

        if (m_avFileFormatList.size() > 0)
            emit ui->tableWidget->cellClicked(0, 0);

//        for (int i = 0 ; i < 5 ; i++)
//        {
//            if (i < m_avFileFormatList.size())
//            {

//                QTableWidgetItem* indexItem = new QTableWidgetItem(QString::number(i + 1));

//                qDebug() << i;
//                qDebug() << getSpeedValue(m_avFileFormatList[i].captureSpeed.mid(1, 4).toFloat());
//                QTableWidgetItem* item = new QTableWidgetItem(getSpeedValue(m_avFileFormatList[i].captureSpeed.mid(1, 4).toFloat()) + speedUnitValue()+", " + QString("%0%1:%2%3:%4%5").arg(m_avFileFormatList[i].time[0]).arg(m_avFileFormatList[i].time[1]).arg(m_avFileFormatList[i].time[2]).arg(m_avFileFormatList[i].time[3]).arg(m_avFileFormatList[i].time[4]).arg(m_avFileFormatList[i].time[5]));
//                ui->tableWidget->setItem(i, 0, indexItem);
//                ui->tableWidget->setItem(i++, 1, item);
//            }

//        }

    }
}


void FileManagerWidget::on_firstPushButton_clicked()
{
    ui->tableWidget->clear();
    if (m_avFileFormatList.size() ==  0)
        return;

    m_AVFileFormatIndex = 0;
    setTableContent();
}

void FileManagerWidget::on_previousPushButton_clicked()
{
    ui->tableWidget->clear();
    if (m_avFileFormatList.size() ==  0)
        return;


    if (m_AVFileFormatIndex - 5 >= 0)
        m_AVFileFormatIndex -= 5;
    setTableContent();
}

void FileManagerWidget::on_nextPushButton_clicked()
{
    ui->tableWidget->clear();
    if (m_avFileFormatList.size() ==  0)
        return;


    if (m_avFileFormatList.size() > m_AVFileFormatIndex + 5)
        m_AVFileFormatIndex += 5;
    setTableContent();
}
 void FileManagerWidget::on_lastPushButton_clicked()
{
    ui->tableWidget->clear();
    if (m_avFileFormatList.size() ==  0)
        return;

    if ((m_avFileFormatList.size() % 5) != 0)
        m_AVFileFormatIndex = m_avFileFormatList.size() - (m_avFileFormatList.size() % 5);
    else
        m_AVFileFormatIndex = m_avFileFormatList.size() - 5;
    setTableContent();
}



//void FileManagerWidget::on_tableWidget_cellClicked(int row, int column)
//{
////    QAbstractTableModel *model = new QAbstractTableModel();
//    QModelIndex nIndex = QAbstractItemModel::createIndex(row, column);
//    // then you can do something like
////    QModelIndex nIndex = model->index(row,column);
////    QModelIndex index;
//    on_tableWidget_clicked(nIndex);
//}


void FileManagerWidget::on_tableWidget_cellClicked(int row, int column)
{
    if (m_avFileFormatList.size() == 0)
        return;

    if (m_avFileFormatList.size() > (row + m_AVFileFormatIndex))
        m_currentAVFileFormat = m_avFileFormatList[row+ m_AVFileFormatIndex];
    else
        return;

    int size = 5;
    if (m_avFileFormatList.size() - 5 <= m_AVFileFormatIndex && m_avFileFormatList.size() % 5 != 0)
        size = m_avFileFormatList.size() % 5;

    ui->tableWidget->item(row, 0)->setTextColor(Qt::red);
    ui->tableWidget->item(row, 1)->setTextColor(Qt::red);
    ui->tableWidget->item(row, 0)->setSelected(true);
    ui->tableWidget->item(row, 1)->setSelected(true);

    for (int i = 0 ; i < size ; i++)
    {
        if (row != i)
        {
            ui->tableWidget->item(i, 0)->setTextColor(Qt::black);
            ui->tableWidget->item(i, 1)->setTextColor(Qt::black);
            ui->tableWidget->item(i, 0)->setSelected(false);
            ui->tableWidget->item(i, 1)->setSelected(false);
        }
    }

    convertValue();

    if (!strncmp(m_currentAVFileFormat.filePrefix, "VV", 2))
    {
//        m_videoWidget->show();
//        ui->frameLabel->hide();
        m_player->setSource(m_avFileFormatList[row+ m_AVFileFormatIndex].file_path);
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_play.png");

        m_player->play();
        m_player->pause();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "AV", 2))
    {
//        m_videoWidget->show();
//        ui->frameLabel->hide();
        m_player->setSource(m_avFileFormatList[row+ m_AVFileFormatIndex].file_path);
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_play.png");


        m_player->play();
        m_player->pause();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "SR", 2))
    {
//        m_videoWidget->show();
//        ui->frameLabel->hide();
        m_player->setSource(m_avFileFormatList[row+ m_AVFileFormatIndex].file_path);
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_play.png");

        m_player->play();
        m_player->pause();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "MV", 2))
    {
//        m_videoWidget->show();
//        ui->frameLabel->show();
        m_player->setSource(m_avFileFormatList[row+ m_AVFileFormatIndex].file_path);
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_play.png");

        m_player->play();
        m_player->pause();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "AI", 2))
    {
//        ui->frameLabel->show();
//        m_videoWidget->hide();
        ui->frameLabel->setImage(m_avFileFormatList[row+ m_AVFileFormatIndex].file_path, ui->frameLabel->size());
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_zoom.png");

        QPixmap pixmap;
        pixmap.load(m_avFileFormatList[row+ m_AVFileFormatIndex].file_path);
        m_image = pixmap.toImage();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "SC", 2))
    {
//        ui->frameLabel->show();
//        m_videoWidget->hide();
        ui->frameLabel->setImage(m_avFileFormatList[row+ m_AVFileFormatIndex].file_path, ui->frameLabel->size());
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_zoom.png");
        QPixmap pixmap;
        pixmap.load(m_avFileFormatList[row+ m_AVFileFormatIndex].file_path);
        m_image = pixmap.toImage();

    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "MC", 2))
    {
//        ui->frameLabel->show();
//        m_videoWidget->hide();
        ui->frameLabel->setImage(m_avFileFormatList[row+ m_AVFileFormatIndex].file_path, ui->frameLabel->size());
        ui->zoomPlayPushButton->setImage("file_manager", "file_management_zoom.png");
        QPixmap pixmap;
        pixmap.load(m_avFileFormatList[row+ m_AVFileFormatIndex].file_path);
        m_image = pixmap.toImage();

    }
}

