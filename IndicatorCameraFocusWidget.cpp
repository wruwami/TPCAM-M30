#include "IndicatorCameraFocusWidget.h"
#include "ui_IndicatorCameraFocusWidget.h"

#include "StringLoader.h"
#include "WidgetSize.h"
#include "ViscaPacket.h"
#include "SerialViscaManager.h"
#include "SerialLaserManager.h"
#include "SpeedUnitManager.h"

extern SerialViscaManager* g_pSerialViscaManager;
extern SerialLaserManager* g_pSerialLaserManager;

IndicatorCameraFocusWidget::IndicatorCameraFocusWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndicatorCameraFocusWidget)
{
    ui->setupUi(this);

    setWindowOpacity(1);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
//    setAttribute(Qt::WA_TranslucentBackground);
    setGeometry(GetWidgetSizePos(QRect(0, 0, 1600, 960)));
//    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));

    m_pserialViscaManager = g_pSerialViscaManager;
    m_pserialLaserManager = g_pSerialLaserManager;

    ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
    ui->speedPushButton->setText(LoadString("IDS_SPEED"));
    ui->autoTriggerPushButton->setText(LoadString("IDS_AT"));
    ui->onePushTriggerPushButton->setText(LoadString("IDS_OPT"));
    ui->forcusDownPushButton->setText(LoadString("IDS_FOCUS_DOWN"));
    ui->forcusPlusPushButton->setText(LoadString("IDS_FOCUS_UP"));
    ui->autoTriggerPushButton->setCheckable(true);
//    ui->autoTriggerPushButton->setStyleSheet("background: transparent;");

    ui->focusLineEdit->SetMode(KeypadType);
    m_pAutoTriggerPushButton = ui->autoTriggerPushButton;
    ui->distanceLabel->setStyleSheet("background: transparent;");

    connect(m_pserialViscaManager->getVisca_packet(), SIGNAL(sig_show_focus(QString)), this, SLOT(on_show_focus(QString)));
    connect(m_pserialLaserManager->getLaser_packet(), SIGNAL(sig_showDistance(float,int)), this, SLOT(showDistanceSensitivity(float, int)));
//    ui->applyPushButton->setText(LoadString("IDS_APPLY"));
    m_pserialViscaManager->show_focusPosition();
}

IndicatorCameraFocusWidget::~IndicatorCameraFocusWidget()
{
    delete ui;
}

void IndicatorCameraFocusWidget::hide()
{
    ui->speedPushButton->hide();
    ui->autoTriggerPushButton->hide();
    ui->onePushTriggerPushButton->hide();
    ui->forcusDownPushButton->hide();
    ui->forcusPlusPushButton->hide();
    ui->focusLineEdit->hide();
}

void IndicatorCameraFocusWidget::show()
{
    ui->speedPushButton->show();
    ui->autoTriggerPushButton->show();
    ui->onePushTriggerPushButton->show();
    ui->forcusDownPushButton->show();
    ui->forcusPlusPushButton->show();
    ui->focusLineEdit->show();
}

void IndicatorCameraFocusWidget::mousePressEvent(QMouseEvent *event)
{
    accept();
}

void IndicatorCameraFocusWidget::on_showHidePushButton_clicked()
{
    m_bHide = !m_bHide;
    if (m_bHide)
    {
        ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
        hide();
    }
    else
    {
        ui->showHidePushButton->setText(LoadString("IDS_SHOW"));
        show();
    }
}

void IndicatorCameraFocusWidget::on_speedPushButton_clicked()
{
    accept();
}



void IndicatorCameraFocusWidget::on_onePushTriggerPushButton_clicked()
{

    m_pserialViscaManager->set_AF_one_push_trigger();
}


void IndicatorCameraFocusWidget::on_forcusDownPushButton_clicked()
{
    m_pserialViscaManager->minus_focus();
    m_pserialViscaManager->show_focusPosition();
//    m_pserialViscaManager.set_focus()
}


void IndicatorCameraFocusWidget::on_forcusPlusPushButton_clicked()
{
    m_pserialViscaManager->plus_focus();
    m_pserialViscaManager->show_focusPosition();
}

void IndicatorCameraFocusWidget::on_show_focus(QString value)
{
    m_FocusValue = value;
    ui->focusLineEdit->setText(value);
}


//void IndicatorCameraFocusWidget::on_applyPushButton_clicked()
//{

//}


void IndicatorCameraFocusWidget::on_autoTriggerPushButton_clicked(bool checked)
{
    if (checked)
    {
        m_pserialLaserManager->start_laser();
        m_pserialLaserManager->request_distance(true);
        ui->autoTriggerPushButton->setStyleSheet("border-color : red;");
    }
    else
    {
        m_pserialLaserManager->stop_laser();
        m_pserialLaserManager->request_distance(false);
        ui->autoTriggerPushButton->setStyleSheet("border-color : blue;");
    }
}

void IndicatorCameraFocusWidget::showDistanceSensitivity(float fSDistance, int nSensitivity)
{
    ui->distanceLabel->setText(QString::number(getDistanceValue(fSDistance), 'f', 1) + distanceValue());
}

