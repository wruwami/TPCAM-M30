#include "FileManagerFileTransferDialog.h"
#include "ui_FileManagerFileTransferDialog.h"

#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimerEvent>

#include "ConfigManager.h"

FileManagerFileTransferDialog::FileManagerFileTransferDialog(QList<AVFileFormat> avFileFormatList, Type type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerFileTransferDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->closePushButton->setStyleSheet("QPushButton {border-image : url(images/MessageBox/closeButton.png); border:none;}");

    m_avFileFormatList = avFileFormatList;

    if (type == FileType)
    {
        TransferFile();
    }
    else
    {
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


    QUrl url;
    url.setScheme("ftp");
    url.setHost(jsonObject["ftp server( dns )"].toString());
//    url.setPath(jsonObject["ftp port"]);
    url.setPort(jsonObject["ftp port"].toInt());
    url.setUserName(jsonObject["ftp user name"].toString());
    url.setPassword(jsonObject["ftp password"].toString());

    QByteArray byte_file;
    QNetworkRequest request(url);
    QNetworkReply* reply;
    int i = 0;
    ui->allProgressBar->setMaximum(m_avFileFormatList.size());
    foreach (auto avFormat, m_avFileFormatList)
    {
        ui->fileNameLabel->setText(QString(avFormat.file_path));
        ui->fileCountLabel->setText(QString("%1 / %2").arg(i + 1).arg(m_avFileFormatList.size()));
        QFile file(QString(avFormat.file_path));
        file.open(QIODevice::ReadOnly);
        byte_file=file.readAll();
        reply = accessManager->put(request, byte_file);
        ui->allProgressBar->setValue(i + 1);
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
    ui->speedLabel->setText(QString("%1 kB/s").arg(bytesSent / bytesTotal));
}

void FileManagerFileTransferDialog::timerEvent(QTimerEvent *event)
{
    ui->remaiTimeLabel->setText(QString("%1").arg(m_second++));
}

void FileManagerFileTransferDialog::TransferFile()
{
    foreach(auto avFormat, m_avFileFormatList)
    {
        QFile file(avFormat.file_path);
        file.copy("/mnt/");
    }
}

//void FileManagerFileTransferDialog::loadError(QNetworkReply::NetworkError)    //Error output during transmission
//{
//    ui->textEdit_Console->append(reply->errorString());
//    qDebug()<<"Error: "<<reply->error();
//}
