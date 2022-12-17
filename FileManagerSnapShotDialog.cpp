#include "FileManagerSnapShotDialog.h"
#include "ui_FileManagerSnapShotDialog.h"

#include "qdir.h"

#include "StringLoader.h"
#include "Color.h"
#include "WidgetSize.h"
#include "CustomScrollbar.h"

FileManagerSnapShotDialog::FileManagerSnapShotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerSnapShotDialog)
{
    ui->setupUi(this);

    resize(GetWidgetSize(QSize(1299, 690)));

    setWindowFlags(Qt::FramelessWindowHint);
    setBackGroundColor(this, 0xffffff);

    ui->snapShotLabel->setText(LoadString("IDC_SNAPSHOT"));
    ui->snapShotIconLabel->setImage("file_manager", "file_management_folder_icon_normal.bmp");
    ui->backPushButton->setText(LoadString("IDS_BACK"));

//    ui->listWidget->setStyleSheet(QString("QListView::item { height: %0px; }").arg(ui->snapShotIconLabel->height()/64* 45));

    addListItem("20170508");
    addListItem("20170510");
    addListItem("20170511");
    addListItem("20170512");
    addListItem("20170514");
    addListItem("20170515");
    addListItem("20170517");
    addListItem("20170518");

//    ui->listWidget->setVerticalScrollBar(new CustomScrollbar(ui->listWidget->width() * 78 / 650));
}

FileManagerSnapShotDialog::~FileManagerSnapShotDialog()
{
    delete ui;
}

void FileManagerSnapShotDialog::addListItem(QString str)
{

    QDir qdir;
//    ui->listWidget->setViewMode(QListView::IconMode);
    QPixmap pixmap;
    pixmap.load(qdir.absolutePath() + "/images/file_manager/file_management_folder_icon_normal.bmp");
    QIcon icon(pixmap);

    QListWidgetItem *item = new QListWidgetItem(str);
    item->setIcon(icon);
    ui->listWidget->addItem(item);
}

void FileManagerSnapShotDialog::on_backPushButton_clicked()
{
    accept();
}

void FileManagerSnapShotDialog::resizeEvent(QResizeEvent *event)
{
    ui->listWidget->setStyleSheet(QString("QListView::item { height: %0px; }").arg(ui->snapShotIconLabel->height()/64* 45));
    ui->listWidget->setVerticalScrollBar(new CustomScrollbar(ui->listWidget->width() * 78 / 650));
}
