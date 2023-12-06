#include "FileManagerFileTransferDialog.h"
#include "ui_FileManagerFileTransferDialog.h"

#include <QThread>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimerEvent>
#include <QFileDialog>
#include <QDirIterator>
#include <QPainter>
#include <QDesktopWidget>

#include <ftplib.h>

#include "ConfigManager.h"
#include "FileManager.h"
#include "StringLoader.h"
#include "WidgetSize.h"
#include "FileManager.h"
#include "CustomPushButton.h"

FileManagerFileTransferDialog::FileManagerFileTransferDialog(TransType type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerFileTransferDialog)
{
    ui->setupUi(this);

    this->setFixedSize(GetWidgetSize(QSize(800, 704)));

    this->setWindowFlags(Qt::FramelessWindowHint);
    m_pClosePushButton = new CustomPushButton(this);
    m_pClosePushButton->setStyleSheet(QString("QPushButton {image : url(%0images/MessageBox/closeButton.png); border : 1px solid blue;}").arg(GeteMMCPath() + "/"));
//    connect(ui->closePushButton, SIGNAL(clicked()), this, SLOT(closeThread()));
    connect(m_pClosePushButton, &QAbstractButton::clicked, this, &QWidget::close);

    QSizePolicy sp_retain = ui->speedLabel->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->speedLabel->setSizePolicy(sp_retain);

//    QSizePolicy sp_retain2 = ui->oneProgressBar->sizePolicy();
//    sp_retain2.setRetainSizeWhenHidden(true);
//    ui->oneProgressBar->setSizePolicy(sp_retain2);
    m_type = type;
    if (type == FileType)
    {
        if (!GetUSBPath().isEmpty())
        {
            ui->titleLabel->setText(LoadString("IDS_FILE_TRANSFER"));
            ui->titleLabel->setFontSize(23);
            m_FileTransThread = new FileTransThread;
            connect(m_FileTransThread, &FileTransThread::finished, m_FileTransThread, &QObject::deleteLater);
//            connect(m_FileTransThread, &FileTransThread::finished, this, &QWidget::close);

            connect(m_FileTransThread, SIGNAL(setValue(int)), this, SLOT(setValue(int)));
            connect(m_FileTransThread, SIGNAL(setMaximum(int)), this, SLOT(setMaximum(int)));
            connect(m_FileTransThread, SIGNAL(setFileNameText(QString)), this, SLOT(setFileNameText(QString)));
            connect(m_FileTransThread, SIGNAL(setFileCountText(QString)), this, SLOT(setFileCountText(QString)));
            connect(m_FileTransThread, SIGNAL(finished()), this, SLOT(closeThread()));


            m_FileTransThread->start();
            startTimer(1000);
        }
    }
    else
    {
        ConfigManager config = ConfigManager("parameter_setting6.json");
        QJsonObject jsonObject = config.GetConfig();

        if (jsonObject["ftp select"].toInt() != 1)
        {
            ui->titleLabel->setText(LoadString("IDS_FTP_TRANSFER"));
            ui->titleLabel->setFontSize(23);
            m_FtpTransThread = new FtpTransThread2;
    //        connect(ui->closePushButton, &QAbstractButton::clicked, m_FtpTransThread.data(), &FtpTransThread2::requestInterruption);

            connect(m_FtpTransThread, &FtpTransThread2::finished, m_FtpTransThread, &QObject::deleteLater);
//            connect(m_FtpTransThread, &FtpTransThread2::finished, this, &QWidget::close);

            connect(m_FtpTransThread, SIGNAL(setValue(int)), this, SLOT(setValue(int)));
            connect(m_FtpTransThread, SIGNAL(setMaximum(int)), this, SLOT(setMaximum(int)));
            connect(m_FtpTransThread, SIGNAL(setFileNameText(QString)), this, SLOT(setFileNameText(QString)));
            connect(m_FtpTransThread, SIGNAL(setFileCountText(QString)), this, SLOT(setFileCountText(QString)));
            connect(m_FtpTransThread, SIGNAL(finished()), this, SLOT(closeThread()));


            m_FtpTransThread->start();
            startTimer(1000);
        }
    }

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());


}

FileManagerFileTransferDialog::~FileManagerFileTransferDialog()
{

//    if (m_FtpTransThread)
//    {
//        m_FtpTransThread->requestInterruption();
//        while (m_FtpTransThread->isRunning())
//        {

//            sleep(1);
//        }
//        m_FtpTransThread->quit();
//        m_FtpTransThread->wait();

//        delete m_FtpTransThread;
//        m_FtpTransThread = nullptr;


//    }
//    if (m_FileTransThread)
//    {
//        m_FileTransThread->requestInterruption();

//        if (m_FileTransThread->isRunning())
//        {
//            sleep(1);
//        }

//        m_FileTransThread->quit();
//        m_FileTransThread->wait();

//        delete m_FileTransThread;
//        m_FileTransThread = nullptr;

//    }

    delete ui;
}

void FileManagerFileTransferDialog::TransferFTP()
{
//    ui->oneProgressBar->setValue(0);
    ui->allProgressBar->setValue(0);
//    buttonsEnabled(true);

//    QNetworkAccessManager *accessManager=new QNetworkAccessManager(this);
//    accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

    ConfigManager config = ConfigManager("parameter_setting6.json");
    QJsonObject jsonObject = config.GetConfig();


    m_index = 0;

    ftplib ftp;/* = new ftplib();*/
//    qDebug() << QString(jsonObject["ftp server( dns )"].toString() + ":" + ;
    ftp.Connect(QString(jsonObject["ftp server( dns )"].toString() + ":" + std::to_string(jsonObject["ftp port"].toInt()).c_str()).toStdString().c_str());
    ftp.Login(jsonObject["ftp user name"].toString().toStdString().c_str(), jsonObject["ftp password"].toString().toStdString().c_str());
    char targetDir[1024];
    ftp.Pwd(targetDir, 1024);

//    ftp_t ftp(jsonObject["ftp server( dns )"].toString().toStdString().c_str(), 21);
//    ftp.login(jsonObject["ftp user name"].toString().toStdString().c_str(), jsonObject["ftp password"].toString().toStdString().c_str());
//    std::string targetDir = ftp.get_file_path();

    QDir qdir(GetSDPath());
    QDirIterator iterDir(GetSDPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (iterDir.hasNext())
    {
        iterDir.next();
        m_count++;
    }

    QDirIterator iterDir3(GetSDPath(), QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (iterDir3.hasNext())
    {
        QString dir = iterDir3.next().replace(GetSDPath(), QString(targetDir));
        dir.replace("\"", "");
        ftp.Mkdir(dir.toStdString().c_str());
     }


    QDirIterator iterDir2(GetSDPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    ui->allProgressBar->setMaximum(m_count);
    ui->allProgressBar->setValue(0);
    int i = 0;
    while (iterDir2.hasNext())
    {
//        i++;
        QString fileName = iterDir2.next().replace(GetSDPath(), QString(targetDir));
        fileName.replace("\"", "");
        QString filePath;
        ftp.Put(iterDir2.next().toStdString().c_str(), fileName.toStdString().c_str(), ftplib::image);
        ui->allProgressBar->setValue((++i) / m_count);
        ui->fileCountLabel->setText(QString("%1 / %2").arg(i).arg(m_count));
        ui->fileNameLabel->setText(fileName);
//        ftp.put_file(fileName.toStdString().c_str());


//        qDebug() << iterDir2.fileInfo().;
        qDebug() << iterDir2.fileName();
        qDebug() << iterDir2.filePath();

//        QString iterDir2.next();

//        QUrl url;
//        url.setScheme("ftp");
//        url.setHost(jsonObject["ftp server( dns )"].toString());

//        url.setPort(jsonObject["ftp port"].toInt());
//        url.setUserName(jsonObject["ftp user name"].toString());
//        url.setPassword(jsonObject["ftp password"].toString());
//        url.setPath(QString(ret.c_str()) + iterDir2.filePath());
////        url.setPath(QString("d:") + iterDir2.filePath().replace("/", "\\"));
////        qDebug() << QString("d:") + iterDir2.filePath().replace("/", "\\");
////        QString file_path(iterDir2.fileName());
////        int index = file_path.lastIndexOf('/');
////        QString file_name = file_path.mid(index + 1, file_path.size() - index - 1);
////        url.setPath(QString(ret.c_str()) + "/" + file_name);

//        ui->fileNameLabel->setText(iterDir2.fileName());

//        QByteArray byte_file;
//        QNetworkRequest request(url);
//        QNetworkReply* reply;

//        QFile file(QString(iterDir2.filePath()));
//        file.open(QIODevice::ReadOnly);
//        byte_file=file.readAll();
//        reply = accessManager->put(request, byte_file);

//        connect(reply, SIGNAL(uploadProgress(qint64 ,qint64)), SLOT(loadProgress(qint64 ,qint64)));
    }
    ftp.Quit();
//    delete ftp;
//    accept();
    emit finished();
//    connect(accessManager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
//    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(loadError(QNetworkReply::NetworkError)));
}

//void FileManagerFileTransferDialog::loadProgress(qint64 bytesSent, qint64 bytesTotal)    //Update progress bar
//{
////    ui->label_Byte->setText(QString("%1 / %2").arg(bytesSent).arg(bytesTotal));
//    ui->oneProgressBar->setMaximum(bytesTotal); //Max
//    ui->oneProgressBar->setValue(bytesSent);  //The current value
//    if (bytesSent != 0 && bytesTotal != 0)
//    {
//        ui->speedLabel->setText(QString("%1 kB/s").arg(bytesSent / bytesTotal));
//        ui->speedLabel->setFontSize(23);
//    }
//}


//void FileManagerFileTransferDialog::replyFinished(QNetworkReply *reply)
//{
//    ui->allProgressBar->setValue(m_index + 1);
//    ui->fileNameLabel->setText(m_file_name);
//    ui->fileNameLabel->setFontSize(23);
//    ui->fileCountLabel->setText(QString("%1 / %2").arg(m_index + 1).arg(m_count));
//    ui->fileCountLabel->setFontSize(23);
//    m_index++;
//}

void FileManagerFileTransferDialog::timerEvent(QTimerEvent *event)
{
    ui->remaiTimeLabel->setText(QString("%1").arg(m_second++));
    ui->remaiTimeLabel->setFontSize(23);
}

void FileManagerFileTransferDialog::TransferFile()
{
//    ui->oneProgressBar->setValue(0);
    ui->allProgressBar->setValue(0);
//    QString dir = QFileDialog::getExistingDirectory(this, "path select", QDir::currentPath(), QFileDialog::ShowDirsOnly);
    QString dir = GetUSBPath();
    QDir qdir(GetSDPath());
    QDirIterator iterDir(GetSDPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (iterDir.hasNext())
    {
        iterDir.next();

        qDebug() << iterDir.fileName();

        m_count++;

//        ui->listWidget->addItem(iterDir.fileName());
    }

    QDirIterator iterDir3(GetSDPath(), QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (iterDir3.hasNext())
    {
        QString dir2 = iterDir3.next().replace(GetSDPath(), QString(dir));
        dir2.replace("\"", "");
//        QDir qdir2(dir2);
        qdir.mkdir(dir2);
//        ftp.Mkdir(dir.toStdString().c_str());
     }

    ui->allProgressBar->setMaximum(m_count);
    int i = 0;
    QDirIterator iterDir2(GetSDPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    ui->allProgressBar->setValue(0);
    while (iterDir2.hasNext())
    {
        iterDir2.next();

        QString fileName = iterDir2.next().replace(GetSDPath(), GetUSBPath());
        fileName.replace("\"", "");
        QString file_path(iterDir2.fileName());
        int index = file_path.lastIndexOf('/');
        QString file_name = file_path.mid(index + 1, file_path.size() - index - 1);
        ui->fileNameLabel->setText(QString(file_name));
        ui->fileNameLabel->setFontSize(23);
        ui->allProgressBar->setValue((++i) / m_count);
        ui->fileCountLabel->setText(QString("%1 / %2").arg(i).arg(m_count));
        ui->fileCountLabel->setFontSize(23);


        QFile file(iterDir2.next());
        ui->allProgressBar->setValue(++i);
//        qDebug() << iterDir2.next();
//        qDebug() << fileName;

        file.copy(fileName);
    }
    emit finished();
    //    accept();
}

void FileManagerFileTransferDialog::setValue(int value)
{
    ui->allProgressBar->setValue(value);
}

void FileManagerFileTransferDialog::setMaximum(int value)
{
    ui->allProgressBar->setMaximum(value);
}

void FileManagerFileTransferDialog::setFileNameText(QString str)
{
    ui->fileNameLabel->setText(str);
}

void FileManagerFileTransferDialog::setFileCountText(QString str)
{
    ui->fileCountLabel->setText(str);
}

void FileManagerFileTransferDialog::closeThread()
{
    switch (m_type)
    {
    case FTPType:
    {
        if (m_FtpTransThread->isRunning())
        {
            m_FtpTransThread->requestInterruption();

        }
        m_FtpTransThread->quit();
        m_FtpTransThread->wait();
//        delete m_FtpTransThread;
//        m_FtpTransThread = nullptr;

    }
        break;
    case FileType:
    {

        if (m_FileTransThread->isRunning())
        {
            m_FileTransThread->requestInterruption();
        }
        m_FileTransThread->quit();
        m_FileTransThread->wait();
//        delete m_FileTransThread;
//        m_FileTransThread = nullptr;
    }
        break;
    }

    sleep(1);
    this->close();

}

//void FileManagerFileTransferDialog::close()
//{
//    switch (m_type)
//    {
//    case FTPType:
//    {
//        m_FtpTransThread->requestInterruption();
//    }
//        break;
//    case FileType:
//    {
//        m_FileTransThread->requestInterruption();
//    }
//        break;
//    }

//    this->close();
//}

void FileManagerFileTransferDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(127,127,127)));
    painter.drawLine(rect().bottomLeft(), rect().bottomRight());
}

void FileManagerFileTransferDialog::resizeEvent(QResizeEvent *event)
{
    int height = ui->horizontalLayout_3->geometry().height();
    int width = ui->horizontalLayout_3->geometry().width();

    int gap = GetWidthWidth(10);
    m_pClosePushButton->setGeometry((QRect(QPoint(width - height+ gap, gap), QSize(height - gap * 2, height - gap * 2))));

}
