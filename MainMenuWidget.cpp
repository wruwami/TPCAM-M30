#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

#include <QTime>

#include "Color.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);
    setBackGroundColor(this, 0x000000);
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui;
}

void MainMenuWidget::SetMainMenuTitle(QString title)
{
    ui->mainMenuTitleLabel->setText(title);
}

void MainMenuWidget::timerEvent(QTimerEvent *event)
{
    ui->timeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
}

