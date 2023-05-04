#include "EnforcementComponentWidget.h"
#include "ui_EnforcementComponentWidget.h"

#include "StringLoader.h"

EnforcementComponentWidget::EnforcementComponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementComponentWidget)
{
    ui->setupUi(this);

    ui->hidePushButton->setText(LoadString("IDS_HIDE"));
    ui->readyPushButton->setText(LoadString("IDS_READY"));
    ui->zoomRangePushButton->setText("Z: 100~160 m");
    ui->dzPlusPushButton->setText(LoadString("IDS_DZ_PLUS"));
    ui->dzMinusPushButton->setText(LoadString("IDS_DZ_MINUS"));

    ui->saveImagePushButton->setText(LoadString("IDS_SAVE_IMAGE"));
    ui->truckPushButton->setImage("enforcement", "truck.jpg");
    ui->bikePushButton->setImage("enforcement", "bike.jpg");

    ui->speedLabel->setText("SL: 100km/h\nT80km/h\nM60km/h");
    ui->speedLabel->setDisabled(true);

    QSizePolicy sp_retain = ui->hidePushButton->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->hidePushButton->setSizePolicy(sp_retain);
    ui->readyPushButton->setSizePolicy(sp_retain);
    ui->zoomRangePushButton->setSizePolicy(sp_retain);
    ui->dzPlusPushButton->setSizePolicy(sp_retain);
    ui->dzMinusPushButton->setSizePolicy(sp_retain);

    ui->saveImagePushButton->setSizePolicy(sp_retain);
    ui->truckPushButton->setSizePolicy(sp_retain);
    ui->bikePushButton->setSizePolicy(sp_retain);

    ui->speedLabel->setSizePolicy(sp_retain);

    ui->enforcementCountLabel->setSizePolicy(sp_retain);
    ui->enforcementDistanceSpeedLabel->setSizePolicy(sp_retain);
    ui->enforcementTimeLabel->setSizePolicy(sp_retain);

}

EnforcementComponentWidget::~EnforcementComponentWidget()
{
    delete ui;
}

void EnforcementComponentWidget::on_hidePushButton_clicked()
{
    m_bHide = !m_bHide;
    if (m_bHide)
    {
        ui->hidePushButton->setText(LoadString("IDS_HIDE"));
        hide();
    }
    else
    {
        ui->hidePushButton->setText(LoadString("IDS_SHOW"));
        show();
    }
}

void EnforcementComponentWidget::hide()
{
    ui->readyPushButton->hide();
    ui->zoomRangePushButton->hide();
    ui->dzPlusPushButton->hide();
    ui->dzMinusPushButton->hide();

    ui->saveImagePushButton->hide();
    ui->truckPushButton->hide();
    ui->bikePushButton->hide();

    ui->speedLabel->hide();

    ui->enforcementCountLabel->hide();
    ui->enforcementDistanceSpeedLabel->hide();
    ui->enforcementTimeLabel->hide();
}

void EnforcementComponentWidget::show()
{
    ui->readyPushButton->show();
    ui->zoomRangePushButton->show();
    ui->dzPlusPushButton->show();
    ui->dzMinusPushButton->show();

    ui->saveImagePushButton->show();
    ui->truckPushButton->show();
    ui->bikePushButton->show();

    ui->speedLabel->show();

    ui->enforcementCountLabel->show();
    ui->enforcementDistanceSpeedLabel->show();
    ui->enforcementTimeLabel->show();
}
