#include "IndicatorCameraExposeWidget.h"
#include "ui_IndicatorCameraExposeWidget.h"

#include <iostream>
#include <vector>
#include <algorithm>

#include "StringLoader.h"
#include "WidgetSize.h"
#include "ConfigManager.h"
#include "iostream"
#include "ViscaPacket.h"
#include "Logger.h"

extern SerialViscaManager* g_pSerialViscaManager;

IndicatorCameraExposeWidget::IndicatorCameraExposeWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndicatorCameraExposeWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    setGeometry(GetWidgetSizePos(QRect(0, 0, 1600, 960)));
//    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));
    setWindowOpacity(1);

    m_serialViscaManager = g_pSerialViscaManager;

    ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
    ui->showHidePushButton->setFontSize(23);
    ui->speedPushButton->setText(LoadString("IDS_SPEED"));
    ui->speedPushButton->setFontSize(23);
    ui->hlcOnPushButton->setText(LoadString("IDS_HLC_OFF"));
    ui->hlcOnPushButton->setFontSize(23);
    ui->defogOffPushButton->setText(LoadString("IDS_DEFOG_OFF"));
    ui->defogOffPushButton->setFontSize(23);
    ui->disOffPushButton->setText(LoadString("IDS_DIS_OFF"));
    ui->disOffPushButton->setFontSize(23);
//    ui->dnrOnPushButton->setText(LoadString("IDS_DNR_ON"));

    ConfigManager gainCon = ConfigManager("gain.json");
    QJsonObject object = gainCon.GetConfig();
//    int count = object["count"].toInt();
    object.remove("count");
//    QStringList value = ;
//    foreach(auto key, object.keys())
//    {
//        QJsonValue item = object.value(key);
//        m_gainList[key] = item.toString();
//    }

//    std::map<std::string, int> gainMap;
//    std::map<std::string, int> irisMap;
//    std::map<std::string, int> shutterSpeedMap;

    foreach (auto item, object.keys())
    {
        bool ok;
        m_gainMap[item.toStdString()] = object.value(item).toString().toInt(&ok, 16);
    }

//    std::vector<std::pair<std::string, int>> vec;
    sort(m_gainMap, m_gainVec);
    for (auto& it : m_gainVec)
    {
        std::string key = it.first;
        int value = it.second;

        QString number;
        number.sprintf("%02X", value);
        ui->gainComboBox->addItem(QString::fromStdString(key), number);
    }

    //make full_gain vector
    object = ConfigManager("gain_full.json").GetConfig();
    object.remove("count");
    foreach (auto item, object.keys())
    {
        bool ok;
        m_gain_fullMap[item.toStdString()] = object.value(item).toString().toInt(&ok, 16);
    }
    sort(m_gain_fullMap, m_gain_fullVec);

    ConfigManager irisCon = ConfigManager("iris.json");
    object = irisCon.GetConfig();
    object.remove("count");
    foreach (auto item, object.keys())
    {
        bool ok;
        m_irisMap[item.toStdString()] = object.value(item).toString().toInt(&ok, 16);
    }
//    vec.clear();
    sort(m_irisMap, m_irisVec);
    for (auto& it : m_irisVec)
    {
        std::string key = it.first;
        int value = it.second;

        QString number;
        number.sprintf("%02X", value);
        ui->irisComboBox->addItem(QString::fromStdString(key), number);
    }
//    foreach (auto item, object.keys())
//    {
//        ui->irisComboBox->addItem(item, object.value(item));
//    }

    //make full_iris vector
    object = ConfigManager("iris_full.json").GetConfig();
    object.remove("count");
    foreach (auto item, object.keys())
    {
        bool ok;
        m_iris_fullMap[item.toStdString()] = object.value(item).toString().toInt(&ok, 16);
    }
    sort(m_iris_fullMap, m_iris_fullVec);

    ConfigManager shutterSpeedCon = ConfigManager("shutter_speed.json");
    object = shutterSpeedCon.GetConfig();
    object.remove("count");
    foreach (auto item, object.keys())
    {
        bool ok;
        m_shutterSpeedMap[item.toStdString()] = object.value(item).toString().toInt(&ok, 16);
    }
//    vec.clear();
    sort(m_shutterSpeedMap, m_shutterSpeedVec);
//    foreach (auto item, object.keys())
//    {
//        ui->shutterSpeedComboBox->addItem(item, object.value(item));
//    }
    for (auto& it : m_shutterSpeedVec)
    {
        std::string key = it.first;
        int value = it.second;

        QString number;
        number.sprintf("%02X", value);
        ui->shutterSpeedComboBox->addItem(QString::fromStdString(key), number);
    }

    for (int i = 0 ; i < 5 ; i++)
    {
        std::string item = QString("DNR %1").arg(i).toStdString();
        ui->dnrComboBox->addItem(item.c_str());
    }

    QStringList dayNights = {"IDS_DAY1", "IDS_DAY2", "IDS_DAY3", "IDS_NIGHT1", "IDS_NIGHT2", "IDS_NIGHT3"};
    for (int i = 0; i < dayNights.size() ; i++)
    {
        ui->daynNightComboBox->addItem(LoadString(dayNights[i].toStdString()));
    }

    ui->daynNightComboBox->setCurrentIndex(0);
//    emit
//    ui->gainComboBox->setCurrentIndex(ui->gainComboBox->count() - 1);
//    ui->irisComboBox->setCurrentIndex(ui->irisComboBox->count() - 1);
//    ui->shutterSpeedComboBox->setCurrentIndex(ui->shutterSpeedComboBox->count() - 1);

    int dnn = ConfigManager("parameter_setting2.json").GetConfig()["day&night selection"].toInt();
    ui->daynNightComboBox->setCurrentIndex(dnn-1);

    connect(m_serialViscaManager->getVisca_packet(), SIGNAL(sig_show_shutter(QString)), this, SLOT(changeShutterUI(QString)));
    connect(m_serialViscaManager->getVisca_packet(), SIGNAL(sig_show_gain(QString)), this, SLOT(changeGainUI(QString)));
    connect(m_serialViscaManager->getVisca_packet(), SIGNAL(sig_show_iris(QString)), this, SLOT(changeIrisUI(QString)));
    connect(m_serialViscaManager->getVisca_packet(), SIGNAL(sig_show_DNR(QString)), this, SLOT(changeDNRUI(QString)));

    startTimer(5000);
    m_bIsConstructionFinished = true;
}

IndicatorCameraExposeWidget::~IndicatorCameraExposeWidget()
{
    delete ui;
}

void IndicatorCameraExposeWidget::mousePressEvent(QMouseEvent *event)
{
//    accept();
}

void IndicatorCameraExposeWidget::on_showHidePushButton_clicked()
{
    m_bHide = !m_bHide;
    if (m_bHide)
    {
        ui->speedPushButton->hide();
        ui->daynNightComboBox->hide();
        ui->gainComboBox->hide();
        ui->irisComboBox->hide();
        ui->shutterSpeedComboBox->hide();
        ui->dnrComboBox->hide();
        ui->hlcOnPushButton->hide();
        ui->defogOffPushButton->hide();
        ui->disOffPushButton->hide();
        ui->showHidePushButton->setText(LoadString("IDS_SHOW"));
    }
    else
    {
        ui->speedPushButton->show();
        ui->daynNightComboBox->show();
        ui->gainComboBox->show();
        ui->irisComboBox->show();
        ui->shutterSpeedComboBox->show();
        ui->dnrComboBox->show();
        ui->hlcOnPushButton->show();
        ui->defogOffPushButton->show();
        ui->disOffPushButton->show();
        ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
    }
}

void IndicatorCameraExposeWidget::on_speedPushButton_clicked()
{
    accept();
}

void IndicatorCameraExposeWidget::on_hlcOnPushButton_clicked()
{
    m_bHLC = !m_bHLC;
    if (m_bHLC)
    {
        m_serialViscaManager->set_HLC_on();
        ui->hlcOnPushButton->setText(LoadString("IDS_HLC_ON"));
    }
    else
    {
        m_serialViscaManager->set_HLC_off();
        ui->hlcOnPushButton->setText(LoadString("IDS_HLC_OFF"));
    }

}


void IndicatorCameraExposeWidget::on_defogOffPushButton_clicked()
{
    m_bDEFOG = !m_bDEFOG;
    if (m_bDEFOG)
    {
        m_serialViscaManager->set_defog_on();
        ui->defogOffPushButton->setText(LoadString("IDS_DEFOG_ON"));
    }
    else
    {
        m_serialViscaManager->set_defog_off();
        ui->defogOffPushButton->setText(LoadString("IDS_DEFOG_OFF"));
    }
}


void IndicatorCameraExposeWidget::on_disOffPushButton_clicked()
{
    m_bDIS = !m_bDIS;
    if (m_bDIS)
    {
        m_serialViscaManager->set_DIS_on();
        ui->disOffPushButton->setText(LoadString("IDS_DIS_ON"));
    }
    else
    {
        m_serialViscaManager->set_DIS_off();
        ui->disOffPushButton->setText(LoadString("IDS_DIS_OFF"));
    }
}

#include <QDebug>

void IndicatorCameraExposeWidget::on_daynNightComboBox_currentIndexChanged(int index)
{
    if(m_bIsConstructionFinished == true)
    {
        QMutexLocker locker(&m_mutex);
        //set combobox items normal
        int irisIndex = ui->irisComboBox->currentIndex();
        QVariant irisVariant = ui->irisComboBox->itemData(irisIndex);

        // Find the first element with the specified second element
        auto itIris = std::find_if(m_irisVec.begin(), m_irisVec.end(),
            [&irisVariant](const std::pair<std::string, int>& element) {
                QString a = irisVariant.toString();
                return element.second == a.toInt(nullptr, 16);
            }
        );
        ui->irisComboBox->setItemText(irisIndex, QString::fromStdString(itIris->first));

        int gainIndex = ui->gainComboBox->currentIndex();
        QVariant gainVariant = ui->gainComboBox->itemData(gainIndex);
        auto itGain = std::find_if(m_gainVec.begin(), m_gainVec.end(),
            [&gainVariant](const std::pair<std::string, int>& element) {
                QString a = gainVariant.toString();
                return element.second == a.toInt(nullptr, 16);
            }
        );
        ui->gainComboBox->setItemText(gainIndex, QString::fromStdString(itGain->first));
    }

    emit sig_dnnIndexChanged(index);

    ConfigManager config = ConfigManager("exposure.json");
    QJsonObject object = config.GetConfig();
    QJsonObject ret;
    switch (index) {
    case 0:
    {
        ret = object["Day"].toObject()["Dark"].toObject();
    }
        break;
    case 1:
    {
        ret = object["Day"].toObject()["Normal"].toObject();
    }
        break;
    case 2:
    {
        ret = object["Day"].toObject()["Bright"].toObject();
    }
        break;
    case 3:
    {
        ret = object["Night"].toObject()["Dark"].toObject();
    }
        break;
    case 4:
    {
        ret = object["Night"].toObject()["Normal"].toObject();
    }
        break;
    case 5:
    {
        ret = object["Night"].toObject()["Bright"].toObject();
    }
        break;
    }

    m_serialViscaManager->set_AE_Mode("03");

    bool ok;
    std::vector<std::pair<std::string, int>>::iterator it;


    int GainValue = ret["Gain"].toString().toInt(&ok, 16);
    foreach (auto item, m_gainVec)
    {
        if (item.second == GainValue)
            ui->gainComboBox->setCurrentText(QString(item.first.c_str()));
    }

    int IrisValue = ret["Iris"].toString().toInt(&ok, 16);
    foreach (auto item, m_irisVec)
    {
        if (item.second == IrisValue)
            ui->irisComboBox->setCurrentText(QString(item.first.c_str()));
    }


    int ShutterValue = ret["Shutter"].toString().toInt(&ok, 16);
//    it = std::find(m_shutterSpeedVec.begin(), m_shutterSpeedVec.end(), ShutterValue);
    foreach (auto item, m_shutterSpeedVec)
    {
        if (item.second == ShutterValue)
            ui->shutterSpeedComboBox->setCurrentText(QString(item.first.c_str()));
    }

//    for (auto it = m_gainMap.begin(); it != m_gainMap.end(); ++it, i++)
//    {
//        if (it->second == ret["Gain"].toInt())
//            ui->gainComboBox->setCurrentIndex(i);
//    }
//    i = 0;
//    for (auto it = m_irisMap.begin(); it != m_irisMap.end(); ++it, i++)
//    {
//        if (it->second == ret["Iris"].toInt())
//            ui->irisComboBox->setCurrentIndex(i);
//    }
//    i = 0;
//    for (auto it = m_shutterSpeedMap.begin(); it != m_shutterSpeedMap.end(); ++it, i++)
//    {
//        if (it->second == ret["Shutter"].toInt())
//            ui->shutterSpeedComboBox->setCurrentIndex(i);
//    }
//    m_serialViscaManager->set_iris(ret["Iris"].toInt());
//    m_serialViscaManager->set_shutter_speed(ret["Shutter"].toInt());
//    m_serialViscaManager->set_gain(ret["Gain"].toInt());
    m_serialViscaManager->set_AE_Mode(ret["Priority"].toString());
    m_serialViscaManager->set_noise_reduction_on(ret["DNR"].toString());
    if (ret["DIS"].toBool())
    {
        m_serialViscaManager->set_DIS_on();
        m_bDIS = true;
        ui->disOffPushButton->setText(LoadString("IDS_DIS_ON"));
    }
    else
    {
        m_serialViscaManager->set_DIS_off();
        m_bDIS = false;
        ui->disOffPushButton->setText(LoadString("IDS_DIS_OFF"));
    }
    if (ret["DEFOG"].toBool())
    {
        m_serialViscaManager->set_defog_on();
        m_bDEFOG = true;
        ui->defogOffPushButton->setText(LoadString("IDS_DEFOG_ON"));
    }
    else
    {
        m_serialViscaManager->set_defog_off();
        m_bDEFOG = false;
        ui->defogOffPushButton->setText(LoadString("IDS_DEFOG_OFF"));
    }
    if(ret["HLC"].toBool())
    {
       m_serialViscaManager->set_HLC_on();
       m_bHLC = true;
       ui->hlcOnPushButton->setText(LoadString("IDS_HLC_ON"));
    }
    else
    {
        m_serialViscaManager->set_HLC_off();
        m_bHLC = false;
        ui->hlcOnPushButton->setText(LoadString("IDS_HLC_OFF"));
    }

//    set_AE_shutter_priority();

    if (index >= 0 && index < 3)
    {
        m_serialViscaManager->set_infrared_mode_off();
        ui->gainComboBox->setDisabled(true);
        ui->irisComboBox->setDisabled(true);
    }
    else
    {
        m_serialViscaManager->set_infrared_mode_on();
        ui->gainComboBox->setDisabled(false);
        ui->irisComboBox->setDisabled(false);
    }
}


void IndicatorCameraExposeWidget::on_gainComboBox_currentIndexChanged(int index)
{
    QMutexLocker locker(&m_mutex);
    m_serialViscaManager->set_gain_from_pq(ui->gainComboBox->itemData(index).toString());
}


void IndicatorCameraExposeWidget::on_irisComboBox_currentIndexChanged(int index)
{
    bool isAutoIris = false;
    int dnn = ConfigManager("parameter_setting2.json").GetConfig()["day&night selection"].toInt();
    if (dnn >= 0 && dnn < 4)
        isAutoIris = true;
    QMutexLocker locker(&m_mutex);
    m_serialViscaManager->set_iris_from_pq(ui->irisComboBox->itemData(index).toString(), true);//isAutoIris);
}

void IndicatorCameraExposeWidget::on_shutterSpeedComboBox_currentIndexChanged(int index)
{
    QMutexLocker locker(&m_mutex);
    m_serialViscaManager->set_shutter_speed_from_pq(ui->shutterSpeedComboBox->itemData(index).toString());
}

void IndicatorCameraExposeWidget::on_dnrComboBox_currentIndexChanged(int index)
{
    QMutexLocker locker(&m_mutex);
    m_serialViscaManager->set_noise_reduction_on(QString::number(index));
}

void IndicatorCameraExposeWidget::timerEvent(QTimerEvent *event)
{
    m_serialViscaManager->read_shutter_speed();
    m_serialViscaManager->read_gain();
    m_serialViscaManager->read_iris();
    m_serialViscaManager->show_noiseReduction();
}

void IndicatorCameraExposeWidget::changeShutterUI(QString strPQ)
{
    if(ui->shutterSpeedComboBox->isEditable() == true)
        return;

    foreach (auto item, m_shutterSpeedVec)
    {
        if (item.second == strPQ.toInt(nullptr,16))
        {
            QMutexLocker locker(&m_mutex);
            ui->shutterSpeedComboBox->setCurrentText(QString(item.first.c_str()));
        }
    }
}

void IndicatorCameraExposeWidget::changeIrisUI(QString strPQ)
{
    if(ui->irisComboBox->isEditable() == true)
        return;

    foreach (auto item, m_iris_fullVec)
    {
        if (item.second == strPQ.toInt(nullptr,16))
        {
            QMutexLocker locker(&m_mutex);
            ui->irisComboBox->setItemText(ui->irisComboBox->currentIndex(), QString(item.first.c_str()));
        }
    }
}

void IndicatorCameraExposeWidget::changeGainUI(QString strPQ)
{
    if(ui->gainComboBox->isEditable() == true)
        return;

    foreach (auto item, m_gain_fullVec)
    {
        if (item.second == strPQ.toInt(nullptr,16))
        {
            QMutexLocker locker(&m_mutex);
            ui->gainComboBox->setItemText(ui->gainComboBox->currentIndex(), QString(item.first.c_str()));
        }
    }
}

void IndicatorCameraExposeWidget::changeDNRUI(QString strP)
{
    ui->shutterSpeedComboBox->setCurrentText(QString("DNR %1").arg(strP.toInt(nullptr,16)));
}
