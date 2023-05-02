#include "FileManagerSnapShotDialog.h"
#include "ui_FileManagerSnapShotDialog.h"

#include "qdir.h"
#include "qdiriterator.h"
#include <QListWidget>

#include "StringLoader.h"
#include "Color.h"
#include "WidgetSize.h"
#include "CustomScrollbar.h"
#include "FileManager.h"

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

    QString folder_path;
    switch (nMode)
    {
        case 0:
    {
        folder_path = GetPath("snapshot/", eMMC);
    }
        break;
    case 1:
    {
        folder_path = GetPath("auto/", eMMC);
    }
        break;
    case 2:
    {
        folder_path = GetPath("video/", eMMC);
    }
        break;
    case 3:
    {
        folder_path = GetPath("manual_capture/", eMMC);
    }
        break;
    }


    QDirIterator it(folder_path, QDir::Dirs/*, QDirIterator::Subdirectories*/);
    while (it.hasNext())
    {
        QString dir = it.next();
        if (dir.mid(dir.size() - 1, 1) == ".")
            continue;

        addListItem(dir);
    }
}

FileManagerSnapShotDialog::~FileManagerSnapShotDialog()
{
    delete ui;
}

void FileManagerSnapShotDialog::addListItem(QString strDate)
{

    QDir qdir;
//    ui->listWidget->setViewMode(QListView::IconMode);
    QPixmap pixmap;
    pixmap.load(qdir.absolutePath() + "/images/file_manager/file_management_folder_icon_normal.bmp");
    QIcon icon(pixmap);

    std::string str = strDate.toStdString();
    int pos = str.rfind('/');
    str = str.substr(pos + 1, str.size() - 8 + 1);
    strDate = QString::fromStdString(str);

    QListWidgetItem *item = new QListWidgetItem(strDate);
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
