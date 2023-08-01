#include "FileManagerFileTransferDialog.h"
#include "ui_FileManagerFileTransferDialog.h"

#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimerEvent>
#include <QFileDialog>

#include "ConfigManager.h"
#include "FileManager.h"
#include "StringLoader.h"
#include "WidgetSize.h"

FileManagerFileTransferDialog::FileManagerFileTransferDialog(QList<AVFileFormat> avFileFormatList, TransType type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerFileTransferDialog)
{
    ui->setupUi(this);

    this->setFixedSize(GetWidgetSize(QSize(800, 704)));

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->closePushButton->setStyleSheet("QPushButton {border-image : url(images/MessageBox/closeButton.png); border:none;}");
    ui->closePushButton->
    connect(ui->closePushButton, &QAbstractButton::clicked, this, &QWidget::close);

    m_avFileFormatList = avFileFormatList;
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


    int i = 0;
    ui->allProgressBar->setMaximum(m_avFileFormatList.size());
    foreach (auto avFormat, m_avFileFormatList)
    {
        QUrl url;
        url.setScheme("ftp");
        url.setHost(jsonObject["ftp server( dns )"].toString());

        url.setPort(jsonObject["ftp port"].toInt());
        url.setUserName(jsonObject["ftp user name"].toString());
        url.setPassword(jsonObject["ftp password"].toString());

        QString file_path(avFormat.file_path);
        int index = file_path.lastIndexOf('/');
        QString file_name = file_path.mid(index + 1, file_path.size() - index - 1);
        url.setPath("/home/firefly/" + file_name);

        ui->fileNameLabel->setText(file_name);


        QByteArray byte_file;
        QNetworkRequest request(url);
        QNetworkReply* reply;

        QFile file(QString(avFormat.file_path));
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

    QString file_path(m_avFileFormatList[m_index].file_path);
    int index = file_path.lastIndexOf('/');
    QString file_name = file_path.mid(index + 1, file_path.size() - index - 1);


    ui->allProgressBar->setValue(m_index + 1);
    ui->fileNameLabel->setText(file_name);
    ui->fileCountLabel->setText(QString("%1 / %2").arg(m_index + 1).arg(m_avFileFormatList.size()));
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
    ui->allProgressBar->setMaximum(m_avFileFormatList.size());
    int i = 0;
    foreach(auto avFormat, m_avFileFormatList)
    {

        ui->fileCountLabel->setText(QString("%1 / %2").arg(i + 1).arg(m_avFileFormatList.size()));
        QString file_path(avFormat.file_path);
        int index = file_path.lastIndexOf('/');
        QString file_name = file_path.mid(index + 1, file_path.size() - index - 1);
        ui->fileNameLabel->setText(QString(file_name));
        QFile file(file_path);
        ui->allProgressBar->setValue(++i);
        file.copy(dir + '/' + file_name);
    }
//    accept();
}
