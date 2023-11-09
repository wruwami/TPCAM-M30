#include "SystemInfoWidget.h"
#include "ui_SystemInfoWidget.h"

#include <QPainter>
#include <QPen>
#include <QJsonArray>
#include <QFile>
#include "qdir.h"
#include <QFileInfo>
#include <QDateTime>
#include <QDebug>

#include "StringLoader.h"
#include "ConfigManager.h"
#include "SpeedUnitManager.h"
#include "SerialLaserManager.h"
#include "SerialViscaManager.h"
#include "ViscaPacket.h"
#include "SerialPacket.h"
#include "FileManager.h"

extern SerialLaserManager* g_pSerialLaserManager;
extern SerialViscaManager* g_pSerialViscaManager;

SystemInfoWidget::SystemInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemInfoWidget)
{
    ui->setupUi(this);

    ui->alignLabel->setText(LoadString("IDS_ALIGN"));
//    ui->alignLabel->setFontSize(23);
    ui->modeLabel->setText(LoadString("IDS_MODE"));
//    ui->modeLabel->setFontSize(23);
    ui->camLabel->setText(LoadString("IDS_CAM_SMALL"));
//    ui->camLabel->setFontSize(23);
    ui->laserLabel->setText(LoadString("IDS_LASER"));
//    ui->laserLabel->setFontSize(23);
    ui->serialNumberLabel->setText(LoadString("IDS_SERIAL_NUMBER"));
//    ui->serialNumberLabel->setFontSize(23);

    QJsonObject object = ConfigManager("setting_reticle.json").GetConfig();
    QJsonArray ar = object["HUD reticle pos"].toArray();
    QJsonArray ar2 = object["Camera reticle pos"].toArray();
    ui->alignValueLabel->setText(QString("H%1, %2, C%3, %4").arg(ar[0].toInt()).arg(ar[1].toInt()).arg(ar2[0].toInt()).arg(ar2[1].toInt()));
//    ui->alignValueLabel->setFontSize(23);
    object = ConfigManager("parameter_setting1.json").GetConfig();
    QString enforcement;
    switch (object["enforcement selection"].toInt())
    {
    case 1:
    {
        enforcement = "I";
    }
        break;
    case 2:
    {
        enforcement = "A";
    }
        break;
    case 3:
    {
        enforcement = "V";
    }
        break;
    }
    QString mode;
    switch (object["speed selection"].toInt())
    {
    case 1:
    {
        mode = "ST";
    }
        break;
    case 2:
    {
        mode = "LT";
    }
    }
    QString zoom_level;
    object = ConfigManager("parameter_enforcement.json").GetConfig();
    int zoom_index = object["zoom_index"].toInt();
    object = ConfigManager("zoom_level.json").GetConfig();
    if (mode == "ST")
    {
        if (distance() == meter)
        {
            zoom_level = object["st mode meter dist"].toArray()[zoom_index].toString();
        }
        else
        {
            zoom_level = object["st mode feet dist"].toArray()[zoom_index].toString();
        }
    }
    else
    {
        if (distance() == meter)
        {
            zoom_level = object["lt mode meter dist"].toArray()[zoom_index].toString();
        }
        else
        {
            zoom_level = object["lt mode feet dist"].toArray()[zoom_index].toString();
        }

    }
    zoom_level = zoom_level.mid(2);
    ui->modeValueLabel->setText(QString("%1(%2, %3%4)").arg(enforcement).arg(mode).arg(zoom_level).arg(distanceValue()));
//    ui->modeValueLabel->setFontSize(23);
    object = ConfigManager("setting_device_ID.json").GetConfig();
    QJsonObject object2 = object["Device ID"].toObject();
    QString SerialNum;
    if (QString::compare(object2["Prefix"].toString(), "null", Qt::CaseInsensitive) && !object2["Prefix"].toString().isEmpty())
        SerialNum.append(object2["Prefix"].toString() + "_" + object2["SerialNum"].toString());
    else
        SerialNum.append(object2["SerialNum"].toString());
    if (QString::compare(object2["Postfix"].toString(), "null", Qt::CaseInsensitive) && !object2["Postfix"].toString().isEmpty())
        SerialNum.append("_" + object2["Postfix"].toString());

    ui->serialNumberValueLabel->setText(SerialNum);
//    ui->serialNumberValueLabel->setFontSize(23);

//    m_SerialViscaManager = new SerialViscaManager;

    connect(g_pSerialViscaManager->getVisca_packet(), SIGNAL(sig_show_version(int, int)), this, SLOT(on_cam_version(int, int)));
    connect(g_pSerialLaserManager->getLaser_packet(), SIGNAL(sig_showVersion(QString)), this, SLOT(on_laser_version(QString)));
    g_pSerialViscaManager->show_camera_version();
    g_pSerialLaserManager->show_laser_info();

    MoveFactorySetting();
}

SystemInfoWidget::~SystemInfoWidget()
{
//    if (m_SerialViscaManager != nullptr)
//    {
//        delete m_SerialViscaManager;
//        m_SerialViscaManager = nullptr;
//    }

    delete ui;
}

void SystemInfoWidget::MoveFactorySetting()
{
    QDir dir = GeteMMCPath() + "/settings";

    foreach (QFileInfo item, dir.entryInfoList())
    {
//        qDebug() << item.fileName();
//        qDebug() << GeteMMCPath() + "/settings/factory/" +item.fileName();
//        qDebug() << GeteMMCPath() + "/settings/" + item.fileName();
        if (item.fileName() == "." || item.fileName() == "..")
            continue;

//        if (QFile::exists(GeteMMCPath() + "/settings/" + item.fileName()))
//        {
//            QFile::remove(GeteMMCPath() + "/settings/" + item.fileName());
//        }
        QDateTime datetime = datetime.currentDateTime();
        QString targetDir = GetSDPath() + "/factory";
        QDir qdir(targetDir);
        if (!qdir.exists())
            qdir.mkdir(targetDir);

        qdir = QDir(targetDir + "/" + datetime.toString("yyMMddhh"));
        if (!qdir.exists())
            qdir.mkdir(targetDir + "/" + datetime.toString("yyMMddhh"));

        if (QFile::exists(targetDir + "/" + datetime.toString("yyMMddhh") + "/" + item.fileName()))
        {
            QFile::remove(targetDir + "/" + datetime.toString("yyMMddhh") + "/" + item.fileName());
        }

        QFile::copy(GeteMMCPath() + "/settings/" +item.fileName(), targetDir + "/" + datetime.toString("yyMMddhh") + "/" + item.fileName());
//        qDebug() << GeteMMCPath() + "/settings/" +item.fileName();
//        qDebug () << GeteMMCPath() + "/factory/" + datetime.toString("yyMMddhh") + "/" + item.fileName();
    }
}


void SystemInfoWidget::paintEvent(QPaintEvent *event)
{
    QPen Pen(Qt::black);
    Pen.setStyle(Qt::DashLine);
    QPainter painter(this);
    painter.setPen(Pen);

    painter.drawLine(0, height()/5, width(), height()/5);
    painter.drawLine(0, height()/5 * 2, width(), height()/5*2);
    painter.drawLine(0, height()/5 * 3, width(), height()/5*3);
    painter.drawLine(0, height()/5 * 4, width(), height()/5*4);
}

void SystemInfoWidget::on_cam_version(int vendor, int version)
{
    QString strVendor;
    if (vendor == 0x78)
        strVendor = "K";
    else if (vendor == 0x20)
        strVendor = "W";

    QString strVersion = QString::number(version, 16);
    QString strVersion2;
    for (int i = 0 ; i < strVersion.length() ; i++)
    {
        if (i == strVersion.length() - 1)
            strVersion2.append(strVersion[i]);
        else
            strVersion2.append(strVersion[i] + ".");
    }

    ui->camValueLabel->setText(QString("v%1(%2)").arg(strVersion2).arg(strVendor));
//    ui->camValueLabel->setFontSize(23);
}

void SystemInfoWidget::on_laser_version(QString version)
{
    ui->laserValueLabel->setText(version);
//    ui->laserValueLabel->setFontSize(23);
}
