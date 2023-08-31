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

#include "CustomPushButton.h"
#include "StringLoader.h"
#include "BaseDialog.h"
#include "FileManagerSnapShotDialog.h"
#include "WidgetSize.h"
#include "KeypadDialog.h"
#include "StillImageViewerDialog.h"
#include "MovieViewerDialog.h"
#include "FileManagerFileTransferDialog.h"
#include "SearchBoxDialog.h"
#include "thermal_printer.h"
#include "FileManager.h"
#include "ImageConverter.h"
#include "WidgetSize.h"
#include "SpeedUnitManager.h"

enum Mode
{
    I_MODE,
    A_MODE,
    V_MODE,
    M_MODE,
    S_MODE,
};

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
    ui->datePushButton->setStyleSheet("QPushButton {background-color: rgba(255,255,255,0); border:none;}");

    ui->firstPushButton->setImage("file_manager", "file_management_prev_big_seek_button.bmp");
    ui->previousPushButton->setImage("file_manager", "file_management_prev_seek_button.bmp");
    ui->nextPushButton->setImage("file_manager", "file_management_next_seek_button.bmp");
    ui->lastPushButton->setImage("file_manager", "file_management_next_big_seek_button.bmp");

//    ui->firstPushButton->setStyleSheet(QString("image: url(images/file_manager/file_management_prev_big_seek_button.png); width: %0; height : %1;").arg(ui->firstPushButton->width(), ui->firstPushButton->height()));
    ui->percentPushButton->setDisabled(true);
    ui->percentPushButton->setText("S:100%");
    ui->connectPushButton->setText(LoadString("IDS_CONNECT"));

    ui->printPushButton->setText(LoadString("IDS_PRINT"));
    ui->printPushButton->setDisabled(true);

    ui->mainMenuPushButton->setText(LoadString("IDS_M"));
    ui->searchPushButton->setText(LoadString("IDS_SEARCH"));
    ui->zoomPlayPushButton->setText(LoadString("IDS_ZOOM"));
    ui->deletePushButton->setText(LoadString("IDS_DELETE"));
    ui->sharePushButton->setText(LoadString("IDS_SHARE"));
    ui->movePushButton->setText(LoadString("IDS_MOVE"));

    ui->horizontalLayout_9->setMargin(GetWidthWidth(15));
    ui->horizontalLayout_9->setSpacing(GetWidthWidth(30));

    m_pHomePushButton = ui->mainMenuPushButton;

    ui->frameLabel->setText(LoadString("IDS_STILL_IMAGE_AND_MOVIE_VIEWER"));
    m_videoWidget = new QVideoWidget;
    ui->verticalLayout->insertWidget(1, m_videoWidget, 335);
//    m_videoWidget->setGeometry(ui->frameLabel->geometry());
    m_videoWidget->hide();


    m_player = new QMediaPlayer(this);
    m_player->setVideoOutput(m_videoWidget);

//    CreateWiFiReadThreadAndInitPrinter();

////    QRect rect = ui->gridLayout_2->contentsRect();
//    int width = ((getScreenWidth() - 15) / 21 * 9);//ui->percentPushButton->width() + ui->connectPushButton->width() + ui->printPushButton->width();
////    int width = ui->horizontalLayout->itemAt(0)->geometry().width();

    QHeaderView *verticalHeader = ui->tableWidget->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Stretch);

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
    startTimer(1000);
}

FileManagerWidget::~FileManagerWidget()
{
    delete m_player;
    delete m_videoWidget;
    delete ui;
}

void FileManagerWidget::setTableContent()
{
    int j = 0;
    for (int i = m_AVFileFormatIndex ; i < m_AVFileFormatIndex + 5 ; i++, j++)
    {
        if (i >= m_avFileFormatList.size())
            break;
        AVFileFormat avfileFormat = m_avFileFormatList[i];
        QTableWidgetItem* indexItem = new QTableWidgetItem(QString::number(i + 1));

        QTableWidgetItem* item = new QTableWidgetItem(avfileFormat.captureSpeed + "km/h, " + QString("%0%1:%2%3:%4%5").arg(avfileFormat.date[0]).arg(avfileFormat.date[1]).arg(avfileFormat.date[2]).arg(avfileFormat.date[3]).arg(avfileFormat.date[4]).arg(avfileFormat.date[5]));
        ui->tableWidget->setItem(j, 0, indexItem);
        ui->tableWidget->setItem(j, 1, item);
    }
}

void FileManagerWidget::resizeEvent(QResizeEvent *event)
{
    int width = ui->tableWidget->size().width();
    ui->tableWidget->setColumnWidth(0, width * 105 / (230 + 105));
    ui->tableWidget->setColumnWidth(1, width * 230 / (230 + 105));

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
    int percent = 0;
    if (m_sdcardManager.GetSDAvailable() != 0 && m_sdcardManager.GetSDTotal() != 0)
        percent = m_sdcardManager.GetSDAvailable() / m_sdcardManager.GetSDTotal();
    ui->percentPushButton->setText(QString("S:%1%").arg(percent));
}

void FileManagerWidget::on_deletePushButton_clicked()
{
    BaseDialog baseDialog(Dialog::FileManagerQuestionMessageWidgetType, Qt::AlignmentFlag::AlignCenter, "");
    if (baseDialog.exec() == QDialog::Accepted)
    {
        BaseDialog baseDialog(Dialog::AdminPWWidgetType, Qt::AlignmentFlag::AlignLeft, "");
        if (baseDialog.exec() == QDialog::Accepted)
        {
            QDirIterator iterDir(GetUSBPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
            while (iterDir.hasNext())
            {
                iterDir.next();

                QFile file(iterDir.filePath());
                file.remove();
            }
            ui->tableWidget->clear();
        //        ui->listWidget->addItem(iterDir.fileName());
            }
//            foreach(auto avFormat, m_avFileFormatList)
//            {
//                QFile file(avFormat.file_path);
//                file.remove();
//                ui->tableWidget->clear();
//            }
        }
    }
}

void FileManagerWidget::convertValue()
{
    snprintf(g_file_elem_for_printer.prefix, 2 + 1, m_currentAVFileFormat.filePrefix);
    snprintf(g_file_elem_for_printer.file_id, 5 + 1, m_currentAVFileFormat.index);
    snprintf(g_file_elem_for_printer.year, 4 + 1, &m_currentAVFileFormat.date[0]);
    snprintf(g_file_elem_for_printer.month, 2 + 1, &m_currentAVFileFormat.date[4]);
    snprintf(g_file_elem_for_printer.day, 2 + 1, &m_currentAVFileFormat.date[6]);
    snprintf(g_file_elem_for_printer.hour, 2 + 1, &m_currentAVFileFormat.time[0]);
    snprintf(g_file_elem_for_printer.minute, 2 + 1, &m_currentAVFileFormat.time[2]);
    snprintf(g_file_elem_for_printer.second, 2 + 1, &m_currentAVFileFormat.time[4]);
    snprintf(g_file_elem_for_printer.msec, 1 + 1, &m_currentAVFileFormat.time[6]);
    snprintf(g_file_elem_for_printer.laser_capture_speed, 5 + 1, m_currentAVFileFormat.captureSpeed.toStdString().c_str());
    snprintf(g_file_elem_for_printer.display_limit_speed, 4 + 1, m_currentAVFileFormat.speedLimit.toStdString().c_str());
    snprintf(g_file_elem_for_printer.capture_limit_speed, 4 + 1, m_currentAVFileFormat.captureSpeedLimit.toStdString().c_str());
    snprintf(g_file_elem_for_printer.laser_capture_distance, 4 + 1, m_currentAVFileFormat.distance.toStdString().c_str());
//    snprintf(g_file_elem_for_printer.user_mode, 1, m_currentAVFileFormat);
//    snprintf(g_file_elem_for_printer.enforcement_mode, 1, m_currentAVFileFormat);
//    snprintf(g_file_elem_for_printer.dual_mode, 1, m_currentAVFileFormat.);
//    snprintf(g_file_elem_for_printer.zoom_level, 2, m_currentAVFileFormat);
    snprintf(g_file_elem_for_printer.latitude, 10 + 1, m_currentAVFileFormat.latitude.toStdString().c_str());
    snprintf(g_file_elem_for_printer.longitude, 11 + 1, m_currentAVFileFormat.longitude.toStdString().c_str());
    sprintf(g_file_elem_for_printer.location, m_currentAVFileFormat.location.toStdString().c_str());
    sprintf(g_file_elem_for_printer.user_name, m_currentAVFileFormat.userId.toStdString().c_str());
    sprintf(g_file_elem_for_printer.device_id, m_currentAVFileFormat.deviceId.toStdString().c_str());
    sprintf(g_file_elem_for_printer.unit, &m_currentAVFileFormat.unit);

}

void FileManagerWidget::on_tableWidget_clicked(const QModelIndex &index)
{
    if (m_avFileFormatList.size() >= (index.row() + m_AVFileFormatIndex))
        m_currentAVFileFormat = m_avFileFormatList[index.row()+ m_AVFileFormatIndex];
    else
        return;

    convertValue();

    if (!strncmp(m_currentAVFileFormat.filePrefix, "VV", 2))
    {
        m_videoWidget->show();
        ui->frameLabel->hide();
        m_player->setMedia(QUrl::fromLocalFile(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path));
        m_player->play();
        m_player->pause();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "AV", 2))
    {
        m_videoWidget->show();
        ui->frameLabel->hide();
        m_player->setMedia(QUrl::fromLocalFile(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path));
        m_player->play();
        m_player->pause();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "SR", 2))
    {
        m_videoWidget->show();
        ui->frameLabel->hide();
        m_player->setMedia(QUrl::fromLocalFile(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path));
        m_player->play();
        m_player->pause();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "MV", 2))
    {
        m_videoWidget->show();
        ui->frameLabel->hide();
        m_player->setMedia(QUrl::fromLocalFile(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path));
        m_player->play();
        m_player->pause();
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "AI", 2))
    {
        ui->frameLabel->show();
        m_videoWidget->hide();
        ui->frameLabel->setImage(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path, ui->frameLabel->size());
    }
    else if (!strncmp(m_currentAVFileFormat.filePrefix, "SC", 2))
    {
        ui->frameLabel->show();
        m_videoWidget->hide();
        ui->frameLabel->setImage(m_avFileFormatList[index.row()+ m_AVFileFormatIndex].file_path, ui->frameLabel->size());
    }
}

void FileManagerWidget::on_searchPushButton_clicked()
{
//    QString title_text = m_currentAVFileFormat.date

    SearchBoxDialog searchBoxDialog(m_dateTime);
    if (searchBoxDialog.exec() == QDialog::Accepted)
    {
        int firstValue = searchBoxDialog.getFirstValue();
        int secondValue = searchBoxDialog.getSecondValue();
        QList<AVFileFormat> avFileFormatList;

        foreach (auto avFormat, m_avFileFormatList)
        {
            int minute = QString(avFormat.time).mid(3, 2).toInt();
            if ( minute >= firstValue && secondValue >= minute)
            {
                avFileFormatList.push_back(avFormat);
            }
        }
        m_avFileFormatList = avFileFormatList;
        setTableContent();
    }
    else
    {

    }
}

void FileManagerWidget::on_zoomPlayPushButton_clicked()
{
    switch (m_nMode)
    {
    case Mode::I_MODE: // I
    {
        StillImageViewerDialog stillImageViewDialog(m_currentAVFileFormat);
        stillImageViewDialog.exec();
    }
        break;
    case Mode::A_MODE: // A
    {
        MovieViewerDialog movieViewerDialog(m_currentAVFileFormat);
        movieViewerDialog.exec();
    }
        break;
    case Mode::V_MODE: // V
    {
        MovieViewerDialog movieViewerDialog(m_currentAVFileFormat);
        movieViewerDialog.exec();
    }
        break;
    case Mode::M_MODE: // Manual Capture
    {
        StillImageViewerDialog stillImageViewDialog(m_currentAVFileFormat);
        stillImageViewDialog.exec();
    }
        break;
    case Mode::S_MODE: // Manual Capture
    {
        MovieViewerDialog movieViewerDialog(m_currentAVFileFormat);
        movieViewerDialog.exec();
    }
        break;

    }

}

void FileManagerWidget::on_sharePushButton_clicked()
{
//    BaseDialog baseDialog(FileManagerFileTransferWidgetType, Qt::AlignmentFlag::AlignCenter, "", true, LoadString("IDS_FTP_FILE_TRANSFER"));
//    baseDialog.exec();
    FileManagerFileTransferDialog fileManagerFileTransferDialog(FTPType);
    fileManagerFileTransferDialog.exec();
}

void FileManagerWidget::on_movePushButton_clicked()
{
//    BaseDialog baseDialog(FileManagerFileTransferWidgetType, Qt::AlignmentFlag::AlignCenter, "", true, LoadString("IDS_USB_MEMORY_TRANSFER"));
//    baseDialog.exec();
    FileManagerFileTransferDialog fileManagerFileTransferDialog(FileType);
    fileManagerFileTransferDialog.exec();

}

void FileManagerWidget::on_printPushButton_clicked()
{
    QImage image(m_currentAVFileFormat.file_path);
    image.convertToFormat(QImage::Format::Format_RGB32);
    ImageConverter imageConvert(image);
    imageConvert.Convert();


//    QImage image2(image.bits(), 1712, 984, QImage::Format::Format_RGB32);
//    int sz2 = image2.byteCount();
//    memcpy(g_print_img_body_buff_file_management , image2.bits(), sz2);

//    pixmap.
    print_wifi_printer();
}

void FileManagerWidget::on_connectPushButton_clicked()
{
//    BaseDialog baseDialog(FileManagerErrorMessageWidgetType, Qt::AlignmentFlag::AlignCenter);
//    baseDialog.exec();

    connect_wifi_printer();
    ui->printPushButton->setDisabled(false);
}

void FileManagerWidget::on_percentPushButton_clicked()
{

}

void FileManagerWidget::on_ImageVideoComboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0: // I
    {
        m_nMode = Mode::I_MODE;
        ui->zoomPlayPushButton->setText(LoadString("IDS_ZOOM"));
    }
        break;
    case 1: // A
    {
        m_nMode = Mode::A_MODE;
        ui->zoomPlayPushButton->setText(LoadString("IDS_PLAY"));
    }
        break;
    case 2: // V
    {
        m_nMode = Mode::V_MODE;
        ui->zoomPlayPushButton->setText(LoadString("IDS_PLAY"));
    }
        break;
    case 3: // M
    {
        m_nMode = Mode::M_MODE;
        ui->zoomPlayPushButton->setText(LoadString("IDS_ZOOM"));
    }
        break;
    case 4: // S
    {
        m_nMode = Mode::S_MODE;
        ui->zoomPlayPushButton->setText(LoadString("IDS_ZOOM"));
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
            m_avFileFormatList.append(avfileFormat);

            QTableWidgetItem* indexItem = new QTableWidgetItem(QString::number(i + 1));

            QTableWidgetItem* item = new QTableWidgetItem(getSpeedValue(avfileFormat.captureSpeed.toFloat()) + speedUnitValue()+", " + QString("%0%1:%2%3:%4%5").arg(avfileFormat.date[0]).arg(avfileFormat.date[1]).arg(avfileFormat.date[2]).arg(avfileFormat.date[3]).arg(avfileFormat.date[4]).arg(avfileFormat.date[5]));
            if (i < 6)
            {
                ui->tableWidget->setItem(i, 0, indexItem);
                ui->tableWidget->setItem(i++, 1, item);
            }
        }
//        date
    }
}


void FileManagerWidget::on_firstPushButton_clicked()
{
    ui->tableWidget->clear();
    if (m_avFileFormatList.size() ==  0)
        return;

    m_AVFileFormatIndex -= 50;
    if (m_AVFileFormatIndex < 0)
        m_AVFileFormatIndex = 0;
    setTableContent();
}

void FileManagerWidget::on_previousPushButton_clicked()
{
    ui->tableWidget->clear();
    if (m_avFileFormatList.size() ==  0)
        return;

    m_AVFileFormatIndex -= 5;
    if (m_AVFileFormatIndex < 0)
        m_AVFileFormatIndex = 0;
    setTableContent();
}

void FileManagerWidget::on_nextPushButton_clicked()
{
    ui->tableWidget->clear();
    if (m_avFileFormatList.size() ==  0)
        return;

    m_AVFileFormatIndex += 5;
    if (m_avFileFormatList.size() <= m_AVFileFormatIndex)
        m_AVFileFormatIndex = m_avFileFormatList.size() - 5;
    setTableContent();
}
 void FileManagerWidget::on_lastPushButton_clicked()
{
    ui->tableWidget->clear();
    if (m_avFileFormatList.size() ==  0)
        return;

    m_AVFileFormatIndex += 50;
    if (m_avFileFormatList.size() <= m_AVFileFormatIndex)
        m_AVFileFormatIndex = m_avFileFormatList.size() - 5;
    setTableContent();
}


