#include "FileManagerWidget.h"
#include "ui_FileManagerWidget.h"

#include <QDebug>
#include <QPainter>

#include "CustomPushButton.h"
#include "StringLoader.h"
#include "BaseDialog.h"

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

    ui->firstPushButton->setImage("file_manager", "file_management_prev_big_seek_button.bmp");
    ui->previousPushButton->setImage("file_manager", "file_management_prev_seek_button.bmp");
    ui->nextPushButton->setImage("file_manager", "file_management_next_seek_button.bmp");
    ui->lastPushButton->setImage("file_manager", "file_management_next_big_seek_button.bmp");

//    ui->percentPushButton->setText(LoadString("IDS_"))
    ui->connectPushButton->setText(LoadString("IDS_CONNECT"));
    ui->printPushButton->setText(LoadString("IDS_PRINT"));

    ui->movePushButton->setText(LoadString("IDS_MOVE"));
    ui->searchPushButton->setText(LoadString("IDS_SEARCH"));
    ui->zoomPushButton->setText(LoadString("IDS_ZOOM"));
    ui->deletePushButton->setText(LoadString("IDS_DELETE"));
    ui->sharePushButton->setText(LoadString("IDS_SHARE"));
    ui->movePushButton->setText(LoadString("IDS_MOVE"));
//    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

FileManagerWidget::~FileManagerWidget()
{
    delete ui;
}

void FileManagerWidget::resizeEvent(QResizeEvent *event)
{

}

void FileManagerWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
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
    BaseDialog baseDialog(Dialog::FileManagerQuestionMessageWidgetType);
    baseDialog.exec();
}
