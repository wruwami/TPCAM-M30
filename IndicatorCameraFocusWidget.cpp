#include "IndicatorCameraFocusWidget.h"
#include "ui_IndicatorCameraFocusWidget.h"

#include "StringLoader.h"
#include "WidgetSize.h"
#include "ViscaPacket.h"
#include "SerialViscaManager.h"
#include "SerialLaserManager.h"
#include "SpeedUnitManager.h"
#include "CustomLineEdit.h"
#include "CustomLabel.h"

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
    ui->showHidePushButton->setFontSize(23);
    ui->speedPushButton->setText(LoadString("IDS_SPEED"));
    ui->speedPushButton->setFontSize(23);
    ui->autoTriggerPushButton->setText(LoadString("IDS_READY"));
    ui->autoTriggerPushButton->setFontSize(23);
    ui->onePushTriggerPushButton->setText(LoadString("IDS_OPT"));
    ui->onePushTriggerPushButton->setFontSize(23);
    ui->forcusDownPushButton->setText(LoadString("IDS_FOCUS_DOWN"));
    ui->forcusDownPushButton->setFontSize(23);
    ui->forcusPlusPushButton->setText(LoadString("IDS_FOCUS_UP"));
    ui->forcusPlusPushButton->setFontSize(23);
    ui->autoTriggerPushButton->setCheckable(true);
    ui->focusLineEdit->setAlignment(Qt::AlignCenter);

//    ui->distanceLabel->setColor(Qt::white);
//    ui->autoTriggerPushButton->setStyleSheet("background: transparent;");

    ui->focusLineEdit->SetMode(KeyboardType);
    m_pAutoTriggerPushButton = ui->autoTriggerPushButton;

    m_pDistanceLabel = new CustomLabel(this);
//    m_pDistanceLabel->setColor(Qt::white);
    m_pDistanceLabel->setAlignment(Qt::AlignCenter);
    m_pDistanceLabel->setGeometry(GetWidgetSizePos(QRect(QPoint(464,595), QSize(678, 115))));
    m_pDistanceLabel->setStyleSheet("color: white; background: transparent;");
    m_pDistanceLabel->setText("----.-m");

    connect(m_pserialViscaManager->getVisca_packet(), SIGNAL(sig_show_focus(QString)), this, SLOT(on_show_focus(QString)));
    connect(m_pserialLaserManager->getLaser_packet(), SIGNAL(sig_showDistance(float,int)), this, SLOT(showDistanceSensitivity(float, int)));
    connect(ui->focusLineEdit, SIGNAL(sig_text(QString)), this, SLOT(on_test(QString)));
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
//    accept();
}

void IndicatorCameraFocusWidget::on_showHidePushButton_clicked()
{
    m_bHide = !m_bHide;
    if (m_bHide)
    {
        ui->showHidePushButton->setText(LoadString("IDS_SHOW"));
        hide();
    }
    else
    {
        ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
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
    m_pserialViscaManager->show_focusPosition();
}


void IndicatorCameraFocusWidget::on_forcusDownPushButton_clicked()
{
    m_pserialViscaManager->minus_focus();
//    ui->focusLineEdit->setText("0x"+m_pserialViscaManager->getFocus_pqrs().toUpper());
}


void IndicatorCameraFocusWidget::on_forcusPlusPushButton_clicked()
{
    m_pserialViscaManager->plus_focus();
//    ui->focusLineEdit->setText("0x"+m_pserialViscaManager->getFocus_pqrs().toUpper());
}

void IndicatorCameraFocusWidget::on_show_focus(QString value)
{
    m_FocusValue = value.toUpper();
    ui->focusLineEdit->setText("0x"+value.toUpper());
}

void IndicatorCameraFocusWidget::on_autoTriggerPushButton_clicked(bool checked)
{
    if (checked)
    {
        m_pserialLaserManager->start_laser();
        m_pserialLaserManager->request_distance(true);
        ui->autoTriggerPushButton->setText(LoadString("IDS_AT"));
        ui->autoTriggerPushButton->setStyleSheet("border-color : red;");
        m_pDistanceLabel->show();
    }
    else
    {
        m_pserialLaserManager->stop_laser();
        m_pserialLaserManager->request_distance(false);
        ui->autoTriggerPushButton->setText(LoadString("IDS_READY"));
        ui->autoTriggerPushButton->setStyleSheet("border-color : blue;");
        m_pDistanceLabel->hide();
    }
}

void IndicatorCameraFocusWidget::showDistanceSensitivity(float fSDistance, int nSensitivity)
{
    if(fSDistance == 9999.0)
        m_pDistanceLabel->setText("----.-" + distanceValue());
    else
        m_pDistanceLabel->setText(QString::number(getDistanceValue(fSDistance), 'f', 1) + distanceValue());

    m_pDistanceLabel->setFontSize(23);
}

void IndicatorCameraFocusWidget::on_test(QString value)
{
    if (value.contains("0x"))
        value.remove(value.indexOf("0x"), 2);
    if (value.contains("0X"))
        value.remove(value.indexOf("0X"), 2);

    ui->focusLineEdit->setText("0x"+value);
    m_pserialViscaManager->set_focus(value);
    m_pserialViscaManager->show_focusPosition();
}

