#include "IndicatorCameraExposeWidget.h"
#include "ui_IndicatorCameraExposeWidget.h"

#include "StringLoader.h"
#include "WidgetSize.h"

IndicatorCameraExposeWidget::IndicatorCameraExposeWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndicatorCameraExposeWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

//    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 960)));
    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));
    setWindowOpacity(1);

    ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
    ui->speedPushButton->setText(LoadString("IDS_SPEED"));
    ui->hlcOnPushButton->setText(LoadString("IDS_HLC_ON"));
    ui->defogOffPushButton->setText(LoadString("IDS_DEFOG_OFF"));
    ui->disOffPushButton->setText(LoadString("IDS_DIS_OFF"));
    ui->dnrOnPushButton->setText(LoadString("IDS_DNR_ON"));

    QStringList dayNights = {"Day1", "Day2", "Day3", "Night1", "Night2", "Night3"};
    ui->daynNightComboBox->addItems(dayNights);
    QStringList gains = {"0dB","7dB","12dB","17dB","22dB","27dB","31dB","36dB","41dB","46dB","51dB"};
    ui->gainComboBox->addItems(gains);
    QStringList Irises;
    for (float i = 1.5; i <= 4.8; i+=0.165)
    {
        QString number;
        number.sprintf("%.3f", i);
        ui->irisComboBox->addItem("F" + number);
    }
    QStringList shutterSpeeds = {"4ms", "2ms", "1.5ms", "1ms", "0.5ms", "0.3ms", "0.2ms"};
    ui->shutterSpeedComboBox->addItems(shutterSpeeds);
    ui->applyPushButton->setText(LoadString("IDS_APPLY"));

    m_serialViscaManager.connectVisca();

}

IndicatorCameraExposeWidget::~IndicatorCameraExposeWidget()
{
    m_serialViscaManager.close();

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
        m_serialViscaManager.set_HLC_on();
        ui->hlcOnPushButton->setText(LoadString("IDS_HLC_ON"));
    }
    else
    {
        m_serialViscaManager.set_HLC_off();
        ui->hlcOnPushButton->setText(LoadString("IDS_HLC_OFF"));
    }

}


void IndicatorCameraExposeWidget::on_defogOffPushButton_clicked()
{
    m_bDEFOG = !m_bDEFOG;
    if (m_bDEFOG)
    {
        m_serialViscaManager.set_defog_on();
        ui->defogOffPushButton->setText(LoadString("IDS_DEFOG_ON"));
    }
    else
    {
        m_serialViscaManager.set_defog_off();
        ui->defogOffPushButton->setText(LoadString("IDS_DEFOG_OFF"));
    }
}


void IndicatorCameraExposeWidget::on_disOffPushButton_clicked()
{
    m_bDIS = !m_bDIS;
    if (m_bDIS)
    {
        m_serialViscaManager.set_DIS_on();
        ui->disOffPushButton->setText(LoadString("IDS_DIS_ON"));
    }
    else
    {
        m_serialViscaManager.set_DIS_off();
        ui->disOffPushButton->setText(LoadString("IDS_DIS_OFF"));
    }
}


void IndicatorCameraExposeWidget::on_dnrOnPushButton_clicked()
{
//    m_bDNR = !m_bDNR;
//    if (m_bDNR)
//    {
//        m_serialViscaManager.set_`;
//        ui->dnrOnPushButton->setText(LoadString("IDS_HLC_ON"));
//    }
//    else
//    {
//        m_serialViscaManager.set_HLC_off();
//        ui->dnrOnPushButton->setText(LoadString("IDS_HLC_OFF"));
//    }
}

