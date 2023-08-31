#include "FileManagerFileTransferDialog.h"
#include "ui_FileManagerFileTransferDialog.h"

#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimerEvent>
#include <QFileDialog>
#include <QDirIterator>

#include "ConfigManager.h"
#include "FileManager.h"
#include "StringLoader.h"
#include "WidgetSize.h"
#include "ftp.hh"

FileManagerFileTransferDialog::FileManagerFileTransferDialog(TransType type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerFileTransferDialog)
{
    ui->setupUi(this);

    this->setFixedSize(GetWidgetSize(QSize(800, 704)));

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->closePushButton->setStyleSheet("QPushButton {border-image : url(images/MessageBox/closeButton.png); border:none;}");
    ui->closePushButton->
    connect(ui->closePushButton, &QAbstractButton::clicked, this, &QWidget::close);

    QSizePolicy sp_retain = ui->speedLabel->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->speedLabel->setSizePolicy(sp_retain);

    QSizePolicy sp_retain2 = ui->oneProgressBar->sizePolicy();
    sp_retain2.setRetainSizeWhenHidden(true);
    ui->oneProgressBar->setSizePolicy(sp_retain2);

    if (type == FileType)
    {
        ui->speedLabel->hide();
        ui->oneProgressBar->hide();
        ui->titleLabel->setText(LoadString("IDS_FILE_TRANSFER"));
        TransferFile();

    }
    else
    {
        ui->titleLabel->setText(LoadString("IDS_FTP_TRANSFER"));
        TransferFTP();
    }

    startTimer(1000);
}

FileManagerFileTransferDialog::~FileManagerFileTransferDialog()
{
    delete ui;
}

void FileManagerFileTransferDialog::TransferFTP()
{
    ui->oneProgressBar->setValue(0);
    ui->allProgressBar->setValue(0);
//    buttonsEnabled(true);

    QNetworkAccessManager *accessManager=new QNetworkAccessManager(this);
    accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

    ConfigManager config = ConfigManager("parameter_setting6.json");
    QJsonObject jsonObject = config.GetConfig();


    m_index = 0;

    ftp_t ftp(jsonObject["ftp server( dns )"].toString().toStdString().c_str(), 21);
    ftp.login(jsonObject["ftp user name"].toString().toStdString().c_str(), jsonObject["ftp password"].toString().toStdString().c_str());
    std::string ret = ftp.get_file_path();
    ftp.logout();

    QDir qdir(GetSDPath());
    QDirIterator iterDir(GetSDPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (iterDir.hasNext())
    {
        iterDir.next();

        qDebug() << iterDir.filePath();
        qDebug() << iterDir.fileName();

        m_count++;

//        ui->listWidget->addItem(iterDir.fileName());
    }

    QDirIterator iterDir2(GetSDPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    ui->allProgressBar->setMaximum(m_count);
    while (iterDir2.hasNext())
    {
        iterDir2.next();
        QUrl url;
        url.setScheme("ftp");
        url.setHost(jsonObject["ftp server( dns )"].toString());

        url.setPort(jsonObject["ftp port"].toInt());
        url.setUserName(jsonObject["ftp user name"].toString());
        url.setPassword(jsonObject["ftp password"].toString());
        url.setPath(QString(ret.c_str()) + "/" + iterDir2.filePath());

//        QString file_path(iterDir2.fileName());
//        int index = file_path.lastIndexOf('/');
//        QString file_name = file_path.mid(index + 1, file_path.size() - index - 1);
//        url.setPath(QString(ret.c_str()) + "/" + file_name);

        ui->fileNameLabel->setText(iterDir2.fileName());

        QByteArray byte_file;
        QNetworkRequest request(url);
        QNetworkReply* reply;

        QFile file(QString(iterDir2.filePath()));
        file.open(QIODevice::ReadOnly);
        byte_file=file.readAll();
        reply = accessManager->put(request, byte_file);

        connect(reply, SIGNAL(uploadProgress(qint64 ,qint64)), SLOT(loadProgress(qint64 ,qint64)));
    }
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
//    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(loadError(QNetworkReply::NetworkError)));
}

void FileManagerFileTransferDialog::loadProgress(qint64 bytesSent, qint64 bytesTotal)    //Update progress bar
{
//    ui->label_Byte->setText(QString("%1 / %2").arg(bytesSent).arg(bytesTotal));
    ui->oneProgressBar->setMaximum(bytesTotal); //Max
    ui->oneProgressBar->setValue(bytesSent);  //The current value
    if (bytesSent != 0 && bytesTotal != 0)
        ui->speedLabel->setText(QString("%1 kB/s").arg(bytesSent / bytesTotal));
}


void FileManagerFileTransferDialog::replyFinished(QNetworkReply *reply)
{
    ui->allProgressBar->setValue(m_index + 1);
    ui->fileNameLabel->setText(m_file_name);
    ui->fileCountLabel->setText(QString("%1 / %2").arg(m_index + 1).arg(m_count));
    m_index++;
}

void FileManagerFileTransferDialog::timerEvent(QTimerEvent *event)
{
    ui->remaiTimeLabel->setText(QString("%1").arg(m_second++));
}

void FileManagerFileTransferDialog::TransferFile()
{
    ui->oneProgressBar->setValue(0);
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

    ui->allProgressBar->setMaximum(m_count);
    int i = 0;
    while (iterDir.hasNext())
    {
        ui->fileCountLabel->setText(QString("%1 / %2").arg(i + 1).arg(m_count));
        QString file_path(iterDir.fileName());
        int index = file_path.lastIndexOf('/');
        QString file_name = file_path.mid(index + 1, file_path.size() - index - 1);
        ui->fileNameLabel->setText(QString(file_name));
        QFile file(file_path);
        ui->allProgressBar->setValue(++i);
        file.copy(dir + '/' + file_name);
    }
//    accept();
}
