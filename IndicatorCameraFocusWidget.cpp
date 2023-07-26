#include "IndicatorCameraFocusWidget.h"
#include "ui_IndicatorCameraFocusWidget.h"

#include "StringLoader.h"
#include "WidgetSize.h"


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

    ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
    ui->speedPushButton->setText(LoadString("IDS_SPEED"));
    ui->autoTriggerPushButton->setText(LoadString("IDS_AT"));
    ui->onePushTriggerPushButton->setText(LoadString("IDS_OPT"));
    ui->forcusDownPushButton->setText(LoadString("IDS_FOCUS_DOWN"));
    ui->forcusPlusPushButton->setText(LoadString("IDS_FOCUS_UP"));

    ui->focusLineEdit->SetMode(KeypadType);
    m_pAutoTriggerPushButton = ui->autoTriggerPushButton;
//    ui->applyPushButton->setText(LoadString("IDS_APPLY"));

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

void IndicatorCameraFocusWidget::on_autoTriggerPushButton_clicked()
{
    switch (m_nMode)
    {
    case Focus_Ready:
    {
        ui->autoTriggerPushButton->setText(LoadString("IDS_AT"));
        m_nMode = Focus_AT;
    }
        break;
    case Focus_AT:
    {
        ui->autoTriggerPushButton->setText(LoadString("IDS_Manual"));
        m_nMode = Focus_Manual;
    }
        break;
    case Focus_Manual:
    {
        ui->autoTriggerPushButton->setText(LoadString("IDS_Ready"));
        m_nMode = Focus_Ready;
    }
        break;
    }
}


void IndicatorCameraFocusWidget::on_onePushTriggerPushButton_clicked()
{

    m_pserialViscaManager.set_AF_one_push_trigger();
}


void IndicatorCameraFocusWidget::on_forcusDownPushButton_clicked()
{
    m_pserialViscaManager.minus_focus();
}


void IndicatorCameraFocusWidget::on_forcusPlusPushButton_clicked()
{
    m_pserialViscaManager.plus_focus();
}


//void IndicatorCameraFocusWidget::on_applyPushButton_clicked()
//{

//}

