#include "IndicatorCameraExposeWidget.h"
#include "ui_IndicatorCameraExposeWidget.h"

#include "StringLoader.h"
#include "WidgetSize.h"
#include "ConfigManager.h"
#include "iostream"

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

    ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
    ui->speedPushButton->setText(LoadString("IDS_SPEED"));
    ui->hlcOnPushButton->setText(LoadString("IDS_HLC_ON"));
    ui->defogOffPushButton->setText(LoadString("IDS_DEFOG_OFF"));
    ui->disOffPushButton->setText(LoadString("IDS_DIS_OFF"));
//    ui->dnrOnPushButton->setText(LoadString("IDS_DNR_ON"));

    m_serialViscaManager = g_pSerialViscaManager;

    QStringList dayNights = {"IDS_DAY1", "IDS_DAY2", "IDS_DAY3", "IDS_NIGHT1", "IDS_NIGHT2", "IDS_NIGHT3"};
    for (int i = 0; i < dayNights.size() ; i++)
    {
        ui->daynNightComboBox->addItem(LoadString(dayNights[i].toStdString()));
    }
    ConfigManager gainCon = ConfigManager("Gain.json");
    QJsonObject object = gainCon.GetConfig();
//    int count = object["count"].toInt();
    object.remove("count");
//    for (int i = 0 ; i < count ; i++)
//    {
//        ui->gainComboBox->addItem(object.keys());
//    }

    foreach (auto item, object.keys())
    {
        ui->gainComboBox->addItem(item, object.value(item));
    }


    ConfigManager irisCon = ConfigManager("Gain.json");
    object = irisCon.GetConfig();
    object.remove("count");
    foreach (auto item, object.keys())
    {
        bool ok;
        irisMap[item.toStdString()] = object.value(item).toString().toInt(&ok, 16);
    }
    vec.clear();
    sort(irisMap, vec);
    for (auto& it : vec)
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

    ConfigManager shutterSpeedCon = ConfigManager("shutter_speed.json");
    object = shutterSpeedCon.GetConfig();
    object.remove("count");
    foreach (auto item, object.keys())
    {
        bool ok;
        shutterSpeedMap[item.toStdString()] = object.value(item).toString().toInt(&ok, 16);
    }
    vec.clear();
    sort(shutterSpeedMap, vec);
//    foreach (auto item, object.keys())
//    {
//        ui->shutterSpeedComboBox->addItem(item, object.value(item));
//    }
    for (auto& it : vec)
    {
        std::string key = it.first;
        int value = it.second;

    m_serialViscaManager = g_pSerialViscaManager;

    for (int i = 0 ; i < 5 ; i++)
    {
        std::string item = QString("DNR %1").arg(i).toStdString();
        ui->dnrComboBox->addItem(item.c_str());
    }

    ui->gainComboBox->setCurrentIndex(ui->gainComboBox->count() - 1);
    ui->irisComboBox->setCurrentIndex(ui->irisComboBox->count() - 1);
    ui->shutterSpeedComboBox->setCurrentIndex(ui->shutterSpeedComboBox->count() - 1);
}

IndicatorCameraExposeWidget::~IndicatorCameraExposeWidget()
{
    delete ui;
}

void IndicatorCameraExposeWidget::mousePressEvent(QMouseEvent *event)
{
    accept();
}

void IndicatorCameraExposeWidget::on_showHidePushButton_clicked()
{
    m_bHide = !m_bHide;
    if (m_bHide)
    {
        ui->hlcOnPushButton->hide();
        ui->defogOffPushButton->hide();
        ui->disOffPushButton->hide();
        ui->showHidePushButton->setText(LoadString("IDS_SHOW"));
    }
    else
    {
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

void IndicatorCameraExposeWidget::on_daynNightComboBox_currentIndexChanged(int index)
{
    m_serialViscaManager->SetDayMode(index + 1);
    if ( index >= 0 && index <= 3)
        m_serialViscaManager->set_infrared_mode_off();
    else if ( index >= 4 && index <= 6)
        m_serialViscaManager->set_infrared_mode_on();
}


void IndicatorCameraExposeWidget::on_gainComboBox_currentIndexChanged(int index)
{
    m_serialViscaManager->set_gain_from_pq(ui->gainComboBox->itemData(index).toString());
}


void IndicatorCameraExposeWidget::on_irisComboBox_currentIndexChanged(int index)
{
    m_serialViscaManager->set_iris_from_pq(ui->irisComboBox->itemData(index).toString());
}


void IndicatorCameraExposeWidget::on_shutterSpeedComboBox_currentIndexChanged(int index)
{
    m_serialViscaManager->set_shutter_speed_from_pq(ui->shutterSpeedComboBox->itemData(index).toString());
}


void IndicatorCameraExposeWidget::on_dnrComboBox_currentIndexChanged(int index)
{
    m_serialViscaManager->set_noise_reduction_on(QString::number(index));
}



