#include "FileManagerSnapShotDialog.h"
#include "ui_FileManagerSnapShotDialog.h"

#include "qdir.h"
#include "qdiriterator.h"
#include <QListWidget>
#include <QPainter>
#include <QDesktopWidget>

#include "StringLoader.h"
#include "Color.h"
#include "WidgetSize.h"
#include "CustomScrollbar.h"
#include "FileManager.h"
#include "CustomPushButton.h"

FileManagerSnapShotDialog::FileManagerSnapShotDialog(int nMode, QWidget *parent) :
    QDialog(parent), ui(new Ui::FileManagerSnapShotDialog)
{
    ui->setupUi(this);

    resize(GetWidgetSize(QSize(1299, 690)));

    setWindowFlags(Qt::FramelessWindowHint);
    setBackGroundColor(this, 0xffffff);

    ui->snapShotLabel->setFontSize(23);
    ui->snapShotIconLabel->setImage("file_manager", "file_management_folder_icon_normal.bmp");
//    ui->backPushButton->setText(LoadString("IDS_BACK"));
    m_pBackPushButton = new CustomPushButton(this);
    m_pBackPushButton->setStyleSheet(QString("QPushButton {image : url(%0images/MessageBox/closeButton.png); border : 1px solid blue;} QPushButton:pressed {border : 1px solid red;}").arg(GeteMMCPath() + "/"));

//    m_pBackPushButton->setGeometry();


//    ui->backPushButton->setFontSize(23);

//    ui->listWidget->setStyleSheet(QString("QListView::item { height: %0px; }").arg(ui->snapShotIconLabel->height()/64* 45));

//    setStyleSheet("border: 5px solid black;");

    QDir dir;

    QString folder_path;
    switch (nMode)
    {
        case 0:
    {
        folder_path = GetPath("/snapshot/", SD);
        ui->snapShotLabel->setText(LoadString("IDC_SNAPSHOT"));
    }
        break;
    case 1:
    {
        folder_path = GetPath("/auto/", SD);
        ui->snapShotLabel->setText(LoadString("IDC_AUTO"));
    }
        break;
    case 2:
    {
        folder_path = GetPath("/video/", SD);
        ui->snapShotLabel->setText(LoadString("IDC_VIDEO"));
    }
        break;
    case 3:
    {
        folder_path = GetPath("/manual_capture/", SD);
        ui->snapShotLabel->setText(LoadString("IDC_MANUAL_CAPTURE"));
    }
        break;
    case 4:
    {
        folder_path = GetPath("/screen/", SD);
        ui->snapShotLabel->setText(LoadString("IDC_SCREEN"));
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

    connect(m_pBackPushButton, &QAbstractButton::clicked, this, &QWidget::close);

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

}

FileManagerSnapShotDialog::~FileManagerSnapShotDialog()
{
    delete m_pBackPushButton;
    delete ui;
}

void FileManagerSnapShotDialog::addListItem(QString strDate)
{

    QDir qdir;
//    ui->listWidget->setViewMode(QListView::IconMode);
    QPixmap pixmap;
    pixmap.load(GeteMMCPath() + "/images/file_manager/file_management_folder_icon_normal.bmp");
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
    ui->listWidget->setStyleSheet(QString("QListView{border:none; } QListView::item { height: %0px; }").arg(ui->snapShotIconLabel->height()* 45/64));
    ui->listWidget->setVerticalScrollBar(new CustomScrollbar(ui->listWidget->width() * 78 / 650));

    int height = ui->horizontalLayout->geometry().height();
    int width = ui->horizontalLayout->geometry().width();

    int gap = GetWidthWidth(10);
    m_pBackPushButton->setGeometry((QRect(QPoint(width - height+ gap, gap), QSize(height - gap * 2, height - gap * 2))));

}

void FileManagerSnapShotDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect = this->rect();

    QPen Pen(Qt::black);
    Pen.setStyle(Qt::SolidLine);
    Pen.setWidth(2);

    painter.setPen(Pen);


    painter.drawRect(rect);
//    rect();

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
