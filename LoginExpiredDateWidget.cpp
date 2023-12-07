#include "LoginExpiredDateWidget.h"
#include "ui_LoginExpiredDateWidget.h"
#include "Logger.h"

#include "StringLoader.h"
#include "SoundPlayer.h"

LoginExpiredDateWidget::LoginExpiredDateWidget(QDialog *parent) :
    QWidget(parent),
    ui(new Ui::LoginExpiredDateWidget)
{
    ui->setupUi(this);

    ui->label->setText(LoadString("IDS_CALIBRATION_SERVICE_REQUIRED"));
//    ui->label->setFontSize(23);
    ui->pushButton->setText(LoadString("IDS_POWER_OFF"));
    ui->pushButton->setFontSize(23);
    m_pParent = parent;
}

LoginExpiredDateWidget::~LoginExpiredDateWidget()
{
    delete ui;
}

void LoginExpiredDateWidget::on_pushButton_clicked()
{
    SoundPlayer soundPlayer("byebye.mp3");
    soundPlayer.play();

    m_pParent->accept();
    SetLogMsg(POWER_OFF);
    system("systemctl poweroff -i");
}

