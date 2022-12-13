#include "IndicatorDialog.h"
#include "ui_IndicatorDialog.h"
#include "CustomPushButton.h"

#include <QFile>
#include <QPainter>

#include "BaseDialog.h"
#include "Color.h"
#include "WidgetSize.h"
#include "StringLoader.h"

#include "IndicatorCameraExposeWidget.h"
#include "IndicatorCameraFocusWidget.h"

IndicatorDialog::IndicatorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndicatorDialog)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    ui->cameraPushButton->setImage("indicator", "camera.jpg");
    ui->daynNightPushButton->setImage("indicator", "indicator_enable_night_mode_off.jpg");
    ui->weatherPushButton->setImage("indicator", "indicator_enable_weather_mode_on.jpg");
    ui->enforcementPushButton->setImage("indicator", "indicator_mode_v.jpg");
    ui->speedPushButton->setImage("indicator", "indicator_enable_user_mode_on.jpg");
    ui->comPushButton->setImage("indicator", "indicator_wifi_disconnected.jpg");
    ui->gpsPushButton->setImage("indicator", "indicator_gps_off.jpg");

    ui->screenRecordingPushButton->setImage("indicator", "screen_recording.jpg");
    ui->onPushButton->setImage("indicator", "screen_recording_on.jpg");
    ui->offPushButton->setImage("indicator", "screen_recording_off.jpg");

    ui->screenRecordingPushButton->setVisible(true);
    ui->onPushButton->setVisible(false);
    ui->offPushButton->setVisible(false);

    m_pCameraExposePushButton = new CustomPushButton;
    m_pCameraFocusPushButton = new CustomPushButton;
}

IndicatorDialog::~IndicatorDialog()
{
//    if (m_pIndicatorCameraFocusWidget != nullptr)
//        delete m_pIndicatorCameraFocusWidget;

//    if (m_pIndicatorCameraExposeWidget != nullptr)
//        delete m_pIndicatorCameraExposeWidget;

    delete ui;
}

void IndicatorDialog::on_cameraPushButton_clicked()
{
    clearSecondRow();

    m_pCameraExposePushButton->setText(LoadString("IDS_EXPOSE"));
    m_pCameraFocusPushButton->setText(LoadString("IDS_FOCUS"));

    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(0));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(1));
    ui->horizontalLayout2->insertWidget(0, m_pCameraExposePushButton, 2);
    ui->horizontalLayout2->insertWidget(1, m_pCameraFocusPushButton, 2);

//    QObject::connect((QWidget*)m_pCameraExposePushButton, SIGNAL(clicked()), this, SLOT(on_cameraExposeClicked()));
//    QObject::connect((QWidget*)m_pCameraFocusPushButton, SIGNAL(clicked()), this, SLOT(on_cameraFocusClicked()));
}

void IndicatorDialog::on_screenRecordingPushButton_clicked()
{
    ui->onPushButton->setVisible(true);
    ui->offPushButton->setVisible(true);
}

void IndicatorDialog::on_daynNightPushButton_clicked()
{
    clearSecondRow();
    m_pDay1PushButton = new CustomPushButton;
    m_pDay2PushButton = new CustomPushButton;
    m_pDay3PushButton = new CustomPushButton;
    m_pNight1PushButton = new CustomPushButton;
    m_pNight2PushButton = new CustomPushButton;
    m_pNight3PushButton = new CustomPushButton;
    m_pDay1PushButton->setImage("indicator", "day1.jpg");
    m_pDay2PushButton->setImage("indicator", "day2.jpg");
    m_pDay3PushButton->setImage("indicator", "day3.jpg");
    m_pNight1PushButton->setImage("indicator", "night1.jpg");
    m_pNight2PushButton->setImage("indicator", "night2.jpg");
    m_pNight3PushButton->setImage("indicator", "night3.jpg");

    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(0));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(1));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(2));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(3));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(5));
    ui->horizontalLayout2->insertWidget(0, m_pDay1PushButton, 2);
    ui->horizontalLayout2->insertWidget(1, m_pDay2PushButton, 2);
    ui->horizontalLayout2->insertWidget(2, m_pDay3PushButton, 2);
    ui->horizontalLayout2->insertWidget(3, m_pNight1PushButton, 2);
    ui->horizontalLayout2->insertWidget(4, m_pNight2PushButton, 2);
    ui->horizontalLayout2->insertWidget(5, m_pNight3PushButton, 2);

}

void IndicatorDialog::on_gpsPushButton_clicked()
{
//    clearSecondRow();
    BaseDialog baseDialog(Dialog::IndicatorGPSWidgetType, Qt::AlignmentFlag::AlignCenter, "", true);
    baseDialog.exec();

}

void IndicatorDialog::on_comPushButton_clicked()
{
    clearSecondRow();
    m_pWifiPushButton = new CustomPushButton();
    m_pBTPushButton = new CustomPushButton();
    m_pEthernetPushButton = new CustomPushButton();
    m_pWifiPushButton->setImage("indicator", "indicator_wifi_connected.jpg");
    m_pBTPushButton->setImage("indicator", "BT.jpg");
    m_pEthernetPushButton->setImage("indicator", "ethernet.png");

    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(6));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(5));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));
    ui->horizontalLayout2->addWidget(m_pWifiPushButton, 2);
    ui->horizontalLayout2->addWidget(m_pBTPushButton, 2);
    ui->horizontalLayout2->addWidget(m_pEthernetPushButton, 2);
}

void IndicatorDialog::on_speedPushButton_clicked()
{
    clearSecondRow();
    m_pSTPushButton = new CustomPushButton();
    m_pLTPushButton = new CustomPushButton();
    m_pSTPushButton->setImage("indicator", "indicator_enable_user_mode_on.jpg");
    m_pLTPushButton->setImage("indicator", "indicator_enable_user_mode_off.jpg");

    ui->horizontalLayout2->setStretch(0, 3);
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(3));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));
    ui->horizontalLayout2->insertWidget(3, m_pSTPushButton, 2);
    ui->horizontalLayout2->insertWidget(4, m_pLTPushButton , 2);
    ui->horizontalLayout2->setStretch(6, 1);

}

void IndicatorDialog::on_enforcementPushButton_clicked()
{
    clearSecondRow();
    m_pImagePushButton = new CustomPushButton();
    m_pVideoPushButton = new CustomPushButton();
    m_pImageVideoPushButton = new CustomPushButton();
    m_pImagePushButton->setImage("indicator", "indicator_mode_i.jpg");
    m_pVideoPushButton->setImage("indicator", "indicator_mode_v.jpg");
    m_pImageVideoPushButton->setImage("indicator", "indicator_mode_a.jpg");

//    ui->gridLayout->setColumnStretch(0, 3);
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(2));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(3));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));

    ui->horizontalLayout2->insertWidget(2, m_pImagePushButton, 2);
    ui->horizontalLayout2->insertWidget(3, m_pImageVideoPushButton , 2);
    ui->horizontalLayout2->insertWidget(4, m_pVideoPushButton , 2);


}

void IndicatorDialog::on_weatherPushButton_clicked()
{
    clearSecondRow();
    m_pSunnyPushButton = new CustomPushButton();
    m_pRainyPushButton = new CustomPushButton();
    m_pSunnyPushButton->setImage("indicator", "indicator_enable_weather_mode_off.jpg");
    m_pRainyPushButton->setImage("indicator", "indicator_enable_weather_mode_on.jpg");

    ui->horizontalLayout2->setStretch(0, 3);
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(1));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(2));
    ui->horizontalLayout2->insertWidget(1, m_pSunnyPushButton, 2);
    ui->horizontalLayout2->insertWidget(2, m_pRainyPushButton ,2);

    ui->horizontalLayout2->setStretch(6, 1);
}

//void IndicatorDialog::on_cameraExposeClicked()
//{
//    if (m_pIndicatorCameraFocusWidget != nullptr)
//    {
//        delete m_pIndicatorCameraFocusWidget;
//        m_pIndicatorCameraFocusWidget = nullptr;
//    }

//    m_pIndicatorCameraExposeWidget = new IndicatorCameraExposeWidget(this);
//    m_pIndicatorCameraExposeWidget->setGeometry(GetWidgetSizePos(QRect(0, 272, 1600, 563)));
//    m_pIndicatorCameraExposeWidget->lower();
//    m_pIndicatorCameraExposeWidget->show();
//}

//void IndicatorDialog::on_cameraFocusClicked()
//{
//    if (m_pIndicatorCameraExposeWidget != nullptr)
//    {
//        delete m_pIndicatorCameraExposeWidget;
//        m_pIndicatorCameraExposeWidget = nullptr;
//    }

//    m_pIndicatorCameraFocusWidget = new IndicatorCameraFocusWidget(this);
//    m_pIndicatorCameraFocusWidget->setGeometry(GetWidgetSizePos(QRect(0, 433, 1600, 402)));
//    m_pIndicatorCameraFocusWidget->lower();
//    m_pIndicatorCameraFocusWidget->show();
//}

void IndicatorDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0,0,0,128)); // 4번째 인자에 적당한 투명도를 입력합니다.
    painter.drawRect(GetWidgetSizePos(QRect(0, 125, 1600,  965)));
//    painter.setBrush(QColor(0,0,0,0)); // 4번째 인자에 적당한 투명도를 입력합니다.
//    painter.drawRect(GetWidgetSizePos(QRect(0, 0, 1600,  125)));
}

void IndicatorDialog::mousePressEvent(QMouseEvent *event)
{
    accept();
}

void IndicatorDialog::clearSecondRow()
{
//    if (m_pIndicatorCameraFocusWidget != nullptr)
//    {
//        delete m_pIndicatorCameraFocusWidget;
//        m_pIndicatorCameraFocusWidget = nullptr;
//    }

//    if (m_pIndicatorCameraExposeWidget != nullptr)
//    {
//        delete m_pIndicatorCameraExposeWidget;
//        m_pIndicatorCameraExposeWidget = nullptr;
//    }

    QLayoutItem* item;
    while ( ( item = ui->horizontalLayout2->takeAt( 0 ) ) != nullptr )
    {
        delete item->widget();
        delete item;
    }

    for (int i = 0 ; i < 7 ; i++)
    {
        QSpacerItem *item2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->horizontalLayout2->addItem(item2);
        ui->horizontalLayout2->setStretch(i, 2);
    }

}

void IndicatorDialog::on_pushButton_clicked()
{
    accept();
}
