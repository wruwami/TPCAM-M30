#include "FileManagerWidget.h"
#include "ui_FileManagerWidget.h"

#include <QDebug>
#include <QPainter>
#include <QHeaderView>

#include "CustomPushButton.h"
#include "StringLoader.h"
#include "BaseDialog.h"
#include "FileManagerSnapShotDialog.h"
#include "WidgetSize.h"
#include "KeypadDialog.h"
#include "StillImageViewerDialog.h"
#include "MovieViewerDialog.h"

enum Mode
{
    I_MODE,
    A_MODE,
    V_MODE,
};

FileManagerWidget::FileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerWidget)
{
    ui->setupUi(this);

    ui->ImageVideoComboBox->addItem(LoadString("IDS_I"));
    ui->ImageVideoComboBox->addItem(LoadString("IDS_A"));
    ui->ImageVideoComboBox->addItem(LoadString("IDS_V"));

    ui->dateImageLabel->setImage("file_manager", "file_management_folder_icon_small.bmp");
    ui->dateLabel->setText(LoadString("IDS_DATE"));

    ui->firstPushButton->setImage("file_manager", "file_management_prev_big_seek_button.png");
    ui->previousPushButton->setImage("file_manager", "file_management_prev_seek_button.png");
    ui->nextPushButton->setImage("file_manager", "file_management_next_seek_button.png");
    ui->lastPushButton->setImage("file_manager", "file_management_next_big_seek_button.png");

//    ui->firstPushButton->setStyleSheet(QString("image: url(images/file_manager/file_management_prev_big_seek_button.png); width: %0; height : %1;").arg(ui->firstPushButton->width(), ui->firstPushButton->height()));
    ui->percentPushButton->setDisabled(true);
    ui->percentPushButton->setText("S:100%");
    ui->connectPushButton->setText(LoadString("IDS_CONNECT"));
    ui->printPushButton->setText(LoadString("IDS_PRINT"));

    ui->mainMenuPushButton->setText(LoadString("IDS_M"));
    ui->searchPushButton->setText(LoadString("IDS_SEARCH"));
    ui->zoomPlayPushButton->setText(LoadString("IDS_ZOOM"));
    ui->deletePushButton->setText(LoadString("IDS_DELETE"));
    ui->sharePushButton->setText(LoadString("IDS_SHARE"));
    ui->movePushButton->setText(LoadString("IDS_MOVE"));

    ui->frameLabel->setText(LoadString("IDS_STILL_IMAGE_AND_MOVIE_VIEWER"));

////    QRect rect = ui->gridLayout_2->contentsRect();
    int width = ((getScreenWidth() - 15) / 21 * 9);//ui->percentPushButton->width() + ui->connectPushButton->width() + ui->printPushButton->width();
////    int width = ui->horizontalLayout->itemAt(0)->geometry().width();
//    ui->tableWidget->setColumnWidth(0, width * 105 / (230 + 105));
//    ui->tableWidget->setColumnWidth(1, width * 230 / (230 + 105));


//    QHeaderView *verticalHeader = ui->tableWidget->verticalHeader();
//    verticalHeader->setSectionResizeMode(QHeaderView::Stretch);
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
}

FileManagerWidget::~FileManagerWidget()
{
    delete ui;
}

void FileManagerWidget::resizeEvent(QResizeEvent *event)
{
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


}

void FileManagerWidget::on_deletePushButton_clicked()
{
    BaseDialog baseDialog(Dialog::FileManagerQuestionMessageWidgetType, Qt::AlignmentFlag::AlignCenter);
    if (baseDialog.exec() == QDialog::Accepted)
    {
        BaseDialog baseDialog(Dialog::AdminPWWidgetType);
        baseDialog.exec();
    }
}

void FileManagerWidget::on_tableWidget_clicked(const QModelIndex &index)
{
    FileManagerSnapShotDialog fileManagerSnapShotDialog;
    fileManagerSnapShotDialog.exec();
}

void FileManagerWidget::on_searchPushButton_clicked()
{
    KeypadDialog keyPadDialog;
    keyPadDialog.exec();
}

void FileManagerWidget::on_zoomPlayPushButton_clicked()
{
    switch (m_nMode)
    {
    case Mode::I_MODE: // I
    {
        StillImageViewerDialog stillImageViewDialog;
        stillImageViewDialog.exec();
    }
        break;
    case Mode::A_MODE: // A
    {
        MovieViewerDialog movieViewerDialog;
        movieViewerDialog.exec();
    }
        break;
    case Mode::V_MODE: // V
    {
        MovieViewerDialog movieViewerDialog;
        movieViewerDialog.exec();
    }
        break;
    }

}

void FileManagerWidget::on_sharePushButton_clicked()
{

}

void FileManagerWidget::on_movePushButton_clicked()
{
    BaseDialog baseDialog(FileManagerFileTransferWidgetType, Qt::AlignmentFlag::AlignCenter, "", true);
    baseDialog.exec();
}

void FileManagerWidget::on_printPushButton_clicked()
{
}

void FileManagerWidget::on_connectPushButton_clicked()
{
    BaseDialog baseDialog(FileManagerErrorMessageWidgetType, Qt::AlignmentFlag::AlignCenter);
    baseDialog.exec();

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
    }
}
