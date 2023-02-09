#include "FileManagerSnapShotDialog.h"
#include "ui_FileManagerSnapShotDialog.h"

#include "qdir.h"
#include "qdiriterator.h"
#include <QListWidget>

#include "StringLoader.h"
#include "Color.h"
#include "WidgetSize.h"
#include "CustomScrollbar.h"

#define DEFAULT_FILE_PATH   "files"

FileManagerSnapShotDialog::FileManagerSnapShotDialog(int nMode, QWidget *parent) :
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

    QDir dir;
    QSet<QString> dirSet;
    QString snapshot_folder_path;
    snapshot_folder_path = dir.absolutePath() + "/" + DEFAULT_FILE_PATH + "/snapshot/";


    QDirIterator it(snapshot_folder_path, QDir::Dirs/*, QDirIterator::Subdirectories*/);
    while (it.hasNext())
    {
        QString dir = it.next();
        if (dir.mid(dir.size() - 1, 1) == ".")
            continue;
        if (nMode == 0 || nMode == 1)
            dirSet.insert(dir);
        //        addListItem(dir);
    }
    QString video_folder_path;
    video_folder_path = dir.absolutePath() + "/" + DEFAULT_FILE_PATH + "/video/";


    QDirIterator it2(video_folder_path, QDir::Dirs/*, QDirIterator::Subdirectories*/);
    while (it2.hasNext())
    {
        QString dir = it2.next();
        if (dir.mid(dir.size() - 1, 1) == ".")
            continue;
        if (nMode == 1 || nMode == 2)
            dirSet.insert(dir);
        //        addListItem(dir);
    }
    foreach(QString dir, dirSet)
    {
        addListItem(dir);
    }
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

//void FileManagerSnapShotDialog::on_listWidget_clicked(const QModelIndex &index)
//{
//    m_strDate = index.data();
//    accept();
//}

QString FileManagerSnapShotDialog::strDate() const
{
    return m_strDate;
}

void FileManagerSnapShotDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    m_strDate = item->text();
    accept();
}
