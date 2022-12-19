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

    }
    else
    {

    }
}
