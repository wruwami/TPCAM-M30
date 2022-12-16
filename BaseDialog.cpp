#include "BaseDialog.h"
#include "ui_BaseDialog.h"

#include <QPen>
#include <QPainter>
#include <QPaintEvent>

#include "Color.h"
#include "StringLoader.h"

#include "SelfTestWarningMessageWidget.h"
#include "LoginExpiredDateWidget.h"
#include "IndicatorGPSWidget.h"
#include "LocationWidget.h"
#include "SystemInfoWidget.h"
#include "FactoryDefaultWidget.h"
#include "AdminPWWidget.h"
#include "PasswordChangingWidget.h"
#include "NetworkPWWidget.h"
#include "WifiSearchWidget.h"
#include "BluetoothSearchFilterWidget.h"
#include "EnforcementWarningMessageWidget.h"
#include "FileManagerErrorMessageWidget.h"
#include "FileManagerQuestionMessageWidget.h"
#include "FileManagerFileTransferWidget.h"

#include "WidgetSize.h"

BaseDialog::BaseDialog(Dialog dialog, Qt::Alignment align, QString msg, bool isCloseButton, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("{border: 1px solid black, background-color : #d9d9d9}");

    if (isCloseButton)
    {
        ui->closePushButton->show();
        ui->closePushButton->setImage("MessageBox", "closeButton.png");
        ui->closePushButton->setStyleSheet("QPushButton {background-color : rgba(255,255,255,0); border:none;}");
    }
    else
    {
        ui->closePushButton->hide();
    }

    align |= Qt::AlignVCenter;

    switch (dialog)
    {
    case Dialog::SelfTestWarningMessageWidgetType:
    {
        ui->verticalLayout->addWidget(new SelfTestWarningMessageWidget(this));
        ui->titleLabel->setText(LoadString("IDS_WARNING_MESSAGE"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 694);
    }
        break;
    case Dialog::LoginExpiredDateWidgetType:
    {
        ui->verticalLayout->addWidget(new LoginExpiredDateWidget(this));
        ui->titleLabel->setText(LoadString("IDS_LOGIN_EXPIRED_DATE"));
        ui->titleLabel->setAlignment(align);
        setSize(1146,604);
    }
    break;
    case Dialog::IndicatorGPSWidgetType:
    {
        ui->verticalLayout->addWidget(new IndicatorGPSWidget(this));
        ui->titleLabel->setText(LoadString("IDS_INDICATOR_GPS"));
        ui->titleLabel->setAlignment(align);
        setSize(745, 635);
    }
        break;
    case Dialog::Setting1LocationWidgetType:
    {
        ui->verticalLayout->addWidget(new LocationWidget(this));
        ui->titleLabel->setText(LoadString("IDS_LOCATION"));
        ui->titleLabel->setAlignment(align);
        setSize(734, 635);
    }
        break;
    case Dialog::Setting3SystemInfoWidgetType:
    {
        ui->verticalLayout->addWidget(new SystemInfoWidget(this));
        ui->titleLabel->setText(LoadString("IDS_SYSTEM_INFO"));
        ui->titleLabel->setAlignment(align);
        setSize(745, 635);
    }
        break;
    case Dialog::Setting3FactoryDefaultWidgetType:
    {
        ui->verticalLayout->addWidget(new FactoryDefaultWidget(this));
        ui->titleLabel->setText(LoadString("IDS_FACTORY_DEFAULT"));
        ui->titleLabel->setAlignment(align);
        setSize(1139, 600);
    }
        break;
    case Dialog::AdminPWWidgetType:
    {
        ui->verticalLayout->addWidget(new AdminPWWidget(msg, this));
        ui->titleLabel->setText(LoadString("IDS_ADMIN_PW"));
        ui->titleLabel->setAlignment(align);
        setSize(1139, 600);
    }
        break;
    case Dialog::PasswordChangingWidgetType:
    {
        ui->verticalLayout->addWidget(new PasswordChangingWidget(this));
        ui->titleLabel->setText(LoadString("IDS_PASSWORD_CHANGING"));
        ui->titleLabel->setAlignment(align);
        setSize(1208, 655);
    }
        break;
    case Dialog::NetworkPWWidgetType:
    {
        ui->verticalLayout->addWidget(new NetworkPWWidget(this));
        ui->titleLabel->setText(LoadString("IDS_NETWORK_PW"));
        ui->titleLabel->setAlignment(align);
        setSize(1139, 600);
    }
        break;
    case Dialog::WifiSearchWidgetType:
    {
        ui->verticalLayout->addWidget(new WifiSearchWidget(this));
        ui->titleLabel->setText(LoadString("IDS_WIFI_SEARCH"));
        ui->titleLabel->setAlignment(align);
        setSize(1208, 635);
    }
        break;
    case Dialog::BluetoothSearchFilterWidgetType:
    {
        ui->verticalLayout->addWidget(new BluetoothSearchFilterWidget(this));
        ui->titleLabel->setText(LoadString("IDS_BLUETOOTH_SEARCH_FILTER"));
        ui->titleLabel->setAlignment(align);
        setSize(1208, 631);
    }
        break;
    case Dialog::EnforcementWarningMessageWidgetType:
    {
        ui->verticalLayout->addWidget(new EnforcementWarningMessageWidget(this));
        ui->titleLabel->setText(LoadString("IDS_ENFORCEMENT_WARNING_MESSAGE"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 694);
    }
        break;
    case Dialog::FileManagerErrorMessageWidgetType:
    {
        ui->verticalLayout->addWidget(new FileManagerErrorMessageWidget(this));
        ui->titleLabel->setText(LoadString("IDS_FILEMANAGER_ERROR_MESSAGE"));
        ui->titleLabel->setAlignment(align);
        setSize(1208, 514);
    }
        break;
    case Dialog::FileManagerQuestionMessageWidgetType:
    {
        ui->verticalLayout->addWidget(new FileManagerQuestionMessageWidget(this));
        ui->titleLabel->setText(LoadString("IDS_FILEMANAGER_QUESTION_MESSAGE"));
        ui->titleLabel->setAlignment(align);
        setSize(1208, 689);
    }
        break;
    case Dialog::FileManagerFileTransferWidgetType:
    {
        ui->verticalLayout->addWidget(new FileManagerFileTransferWidget(this));
        ui->titleLabel->setText(LoadString("IDS_FILEMANAGER_FILE_TRANSFER"));
        ui->titleLabel->setAlignment(align);
        setSize(1208, 702);
    }
        break;

    default:
    {
//        throw std::not_implement
    }
        break;
    }

//    if (isClosebutton)


}

BaseDialog::~BaseDialog()
{
    delete ui->verticalLayout->widget();
    delete ui;
}

void BaseDialog::setSize(QSize size)
{
//    ui->verticalLayout->itemAt(0)->widget()->resize(GetWidgetSize(QSize(size.width(), 130)));
//    ui->titleLabel->resize(GetWidgetSize(QSize(size.width(), 130)));
//    ui->verticalLayout->itemAt(1)->widget()->resize(GetWidgetSize(QSize(size.width(), size.height() - 130)));

    resize(GetWidgetSize(size));
    ui->verticalLayout->setStretch(0, 130);
    ui->verticalLayout->setStretch(1, size.height() - 130);
//    ui->titleLabel->resize(GetWidgetSize(QSize(size.width(), 130)));
}

void BaseDialog::setSize(int w, int h)
{
//    ui->verticalLayout->itemAt(0)->widget()->resize(GetWidgetSize(QSize(w, 130)));
//    ui->verticalLayout->itemAt(1)->widget()->resize(GetWidgetSize(QSize(w, h - 130)));
    resize(GetWidgetSize(QSize(w, h)));
    ui->verticalLayout->setStretch(0, 130);
    ui->verticalLayout->setStretch(1, h - 130);
//    ui->titleLabel->resize(GetWidgetSize(QSize(w, 130)));
}



void BaseDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(127,127,127)));
    QRect rect = ui->verticalLayout->itemAt(0)->geometry();
    painter.drawLine(rect.bottomLeft(), rect.bottomRight());
}

void BaseDialog::on_closePushButton_clicked()
{
    accept();
}
