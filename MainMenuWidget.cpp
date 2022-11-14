#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

#include <QTime>

#include "Color.h"
#include "IndicatorWidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);
    setBackGroundColor(this, 0x000000);

    m_pCameraPushbutton = ui->cameraPushButton;
    m_pDaynNightPushbutton = ui->daynNightPushButton;
    m_pWeatherPushbutton = ui->weatherPushButton;
    m_pEnforcementPushbutton = ui->enforcementPushButton;
    m_pSpeedPushbutton = ui->speedPushButton;
    m_pWifiPushbutton = ui->wifiPushButton;
    m_pGpsPushbutton = ui->gpsPushButton;
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui;
}

void MainMenuWidget::SetMainMenuTitle(QString title)
{
    ui->mainMenuTitleLabel->setText(title);
}

void MainMenuWidget::enableButtons(bool enable)
{
    ui->cameraPushButton->setEnabled(enable);
    ui->daynNightPushButton->setEnabled(enable);
    ui->weatherPushButton->setEnabled(enable);
    ui->enforcementPushButton->setEnabled(enable);
    ui->speedPushButton->setEnabled(enable);
    ui->wifiPushButton->setEnabled(enable);
    ui->gpsPushButton->setEnabled(enable);
}

void MainMenuWidget::timerEvent(QTimerEvent *event)
{
    ui->timeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
}


//void MainMenuWidget::on_cameraPushButton_clicked()
//{

//}

//void MainMenuWidget::on_daynNightPushButton_clicked()
//{

//}

//void MainMenuWidget::on_weatherPushButton_clicked()
//{

//}

//void MainMenuWidget::on_enforcementPushButton_clicked()
//{

//}

//void MainMenuWidget::on_speedPushButton_clicked()
//{

//}

//void MainMenuWidget::on_wifiPushButton_clicked()
//{

//}

//void MainMenuWidget::on_gpsPushButton_clicked()
//{

//}
