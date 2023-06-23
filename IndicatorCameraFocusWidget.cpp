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
//    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 960)));
    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));

    ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
    ui->speedPushButton->setText(LoadString("IDS_SPEED"));
    ui->autoTriggerPushButton->setText(LoadString("IDS_AT"));
    ui->onePushTriggerPushButton->setText(LoadString("IDS_OPT"));
    ui->forcusDownPushButton->setText(LoadString("IDS_FOCUS_DOWN"));
    ui->forcusPlusPushButton->setText(LoadString("IDS_FOCUS_UP"));

    ui->applyPushButton->setText(LoadString("IDS_APPLY"));

    m_serialViscaManager.connectVisca();
}

IndicatorCameraFocusWidget::~IndicatorCameraFocusWidget()
{
    m_serialViscaManager.close();
    delete ui;
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
        ui->showHidePushButton->setText(LoadString("IDS_SHOW"));
    }
    else
    {
        ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
    }
}

void IndicatorCameraFocusWidget::on_speedPushButton_clicked()
{
    accept();
}

void IndicatorCameraFocusWidget::on_autoTriggerPushButton_clicked()
{

}


void IndicatorCameraFocusWidget::on_onePushTriggerPushButton_clicked()
{
    m_serialViscaManager.set_AF_one_push_trigger();
}


void IndicatorCameraFocusWidget::on_forcusDownPushButton_clicked()
{
    m_serialViscaManager.minus_focus();
}


void IndicatorCameraFocusWidget::on_forcusPlusPushButton_clicked()
{
    m_serialViscaManager.plus_focus();
}


void IndicatorCameraFocusWidget::on_applyPushButton_clicked()
{

}

