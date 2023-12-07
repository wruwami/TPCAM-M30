#include "BaseDialog.h"
#include "ui_BaseDialog.h"

#include <QPen>
#include <QPainter>
#include <QPaintEvent>
#include <QDesktopWidget>

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
#include "SearchBoxWidget.h"
#include "SdCardMemoryLack.h"
#include "FileManager.h"
#include "CustomPushButton.h"

#include "WidgetSize.h"

BaseDialog::BaseDialog(Dialog dialog, Qt::Alignment align, QString msg, bool isCloseButton, QString title_text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseDialog)
{
    ui->setupUi(this);
    m_bIsCloseButton = isCloseButton;

    ui->titleLabel->setFontSize(23);

    this->setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//    this->setWindowModality(Qt::ApplicationModal);
//    this->setStyleSheet("{border-width: 5px; border-style: solid; border-color: black; background-color : #d9d9d9;}");
//    this->setAttribute(Qt::WA_StyledBackground);

    if (isCloseButton)
    {
//        ui->closePushButton->show();
////        ui->closePushButton->resize(ui->closePushButton->width(), ui->closePushButton->width());
////        ui->closePushButton->setImage("MessageBox", "closeButton.png", QSize(0,0));
//        ui->closePushButton->setStyleSheet(QString("QPushButton { image : url(%0images/MessageBox/closeButton.png); border : 1px solid blue;} QPushButton:pressed {border : 1px solid red;}").arg(GeteMMCPath() + "/"));
//        connect(ui->closePushButton, &QAbstractButton::clicked, this, &QWidget::close);

        m_pClosePushButton = new CustomPushButton(this);
        m_pClosePushButton->setStyleSheet(QString("QPushButton { image : url(%0images/MessageBox/closeButton.png); border : 1px solid blue;} QPushButton:pressed {border : 1px solid red;}").arg(GeteMMCPath() + "/"));
//        m_pClosePushButton->setGeometry(GetWidgetSizePos(QRect(QPoint(), QSize())));
        connect(m_pClosePushButton, &QAbstractButton::clicked, this, &QWidget::close);

    }
    else
    {
//        ui->closePushButton->hide();
    }

    align |= Qt::AlignVCenter;

    switch (dialog)
    {

    case Dialog::LoginExpiredDateWidgetType:
    {
        ui->verticalLayout->addWidget(new LoginExpiredDateWidget(this));
        ui->titleLabel->setText(LoadString("IDS_LOGIN_EXPIRED_DATE"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);
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
        setSize(1216, 684);
    }
        break;
    case Dialog::AdminPWWidgetType:
    {
        ui->verticalLayout->addWidget(new AdminPWWidget(msg, this));
        ui->titleLabel->setText(LoadString("IDS_ADMIN_PW"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);
    }
        break;
    case Dialog::NetworkPasswordChangingWidgetType:
    {
        ui->verticalLayout->addWidget(new PasswordChangingWidget(true, this));
        ui->titleLabel->setText(title_text);
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);
    }
        break;

    case Dialog::PasswordChangingWidgetType:
    {
        ui->verticalLayout->addWidget(new PasswordChangingWidget(false, this));
        ui->titleLabel->setText(LoadString("IDS_PASSWORD_CHANGING"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);
    }
        break;
    case Dialog::BluetoothSearchFilterWidgetType:
    {
        ui->verticalLayout->addWidget(new BluetoothSearchFilterWidget(this));
        ui->titleLabel->setText(LoadString("IDS_BLUETOOTH_SEARCH_FILTER"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);
    }
        break;
    case Dialog::EnforcementWarningMessageWidgetType:
    {
        ui->verticalLayout->addWidget(new EnforcementWarningMessageWidget(this));
        ui->titleLabel->setText(LoadString("IDS_ENFORCEMENT_WARNING_MESSAGE"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);
    }
        break;
    case Dialog::FileManagerErrorMessageWidgetType:
    {
        ui->verticalLayout->addWidget(new FileManagerErrorMessageWidget(this));
        ui->titleLabel->setText(LoadString("IDS_FILEMANAGER_ERROR_MESSAGE"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);
    }
        break;
    case Dialog::FileManagerQuestionMessageWidgetType:
    {
        ui->verticalLayout->addWidget(new FileManagerQuestionMessageWidget(this));
        ui->titleLabel->setText(LoadString("IDS_FILEMANAGER_QUESTION_MESSAGE"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);
    }
        break;
//    \\case Dialog::FileManagerFileTransferWidgetType:
//    {
//        ui->verticalLayout->addWidget(new FileManagerFileTransferWidget(this));
//        ui->titleLabel->setText(LoadString("IDS_FILEMANAGER_FILE_TRANSFER"));
//        ui->titleLabel->setAlignment(align);
//        setSize(1208, 702);
//    }
//        break;
    case Dialog::SearchBoxType:
    {
        ui->verticalLayout->addWidget(new SearchBoxWidget(this));
        ui->titleLabel->setText(title_text);
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);
    }
        break;
    case Dialog::SdCardMemoryLackType:
    {
        ui->verticalLayout->addWidget(new SdCardMemoryLack(msg, this));
        ui->titleLabel->setText(title_text);
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);
    }
        break;
    case Dialog::WifiSearchWidgetType:
    {
        WifiSearchWidget* wifiSearchWidget = new WifiSearchWidget(this);
        ui->verticalLayout->addWidget(wifiSearchWidget);
        ui->titleLabel->setText(LoadString("IDS_WIFI_SEARCH"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 684);

        connect(wifiSearchWidget, SIGNAL(sig_sendConnectingState(bool)), this, SLOT(changeConnectingState(bool)));
        connect(this, SIGNAL(sig_searchingWIFIDone()), wifiSearchWidget, SLOT(on_startWifySearch()));
    }
        break;

    default:
    {
//        throw std::not_implement
    }
        break;
    }
    if(dialog == WifiSearchWidgetType)
        ui->connectingStateLabel->setText(LoadString(""));
    else
        {
            ui->horizontalLayout->removeWidget(ui->connectingStateLabel);
            ui->connectingStateLabel->hide();
        }

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    //    if (isClosebutton)
}

BaseDialog::BaseDialog(Dialog dialog, Status isCamera, Status isLaser, Status isBattery, Status isStorage, Qt::Alignment align, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseDialog)
{
    ui->setupUi(this);

    this->setWindowFlags( Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//    this->setWindowFlags(Qt::CustomizeWindowHint);
//    this->setStyleSheet("{border-width: 5px; border-style: solid; border-color: black; background-color : #d9d9d9;}");
//    this->setAttribute(Qt::WA_StyledBackground);

//    ui->closePushButton->hide();

    align |= Qt::AlignVCenter;

    switch (dialog)
    {
    case Dialog::SelfTestWarningMessageWidgetType:
    {
        SelfTestWarningMessageWidget* selfTestWarningMessageWidget = new SelfTestWarningMessageWidget(isCamera, isLaser, isBattery, isStorage, this);
        ui->verticalLayout->addWidget(selfTestWarningMessageWidget);
        ui->titleLabel->setText(LoadString("IDS_WARNING_MESSAGE"));
        ui->titleLabel->setAlignment(align);
        setSize(1216, 694);
    }
        break;

    }
    if(dialog == WifiSearchWidgetType)
        ui->connectingStateLabel->setText(LoadString(""));
    else
        {
            ui->horizontalLayout->removeWidget(ui->connectingStateLabel);
            ui->connectingStateLabel->hide();
        }

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    //    if (isClosebutton)
}

//BaseDialog::BaseDialog(Dialog dialog, Qt::Alignment align, QWidget *pWidget, QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::BaseDialog)
//{
//    ui->setupUi(this);

//    this->setWindowFlags( Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
////    this->setWindowFlags(Qt::CustomizeWindowHint);
////    this->setStyleSheet("{border-width: 5px; border-style: solid; border-color: black; background-color : #d9d9d9;}");
////    this->setAttribute(Qt::WA_StyledBackground);

//    ui->closePushButton->hide();

//    align |= Qt::AlignVCenter;

//    switch (dialog)
//    {

//    }
//}

BaseDialog::~BaseDialog()
{
    if (m_pClosePushButton)
    {
        delete m_pClosePushButton;
        m_pClosePushButton = nullptr;
    }

    delete ui->verticalLayout->widget();
    delete ui;
}

void BaseDialog::setAvFileFormatList(QList<AVFileFormat> avFileFormatList)
{

}

void BaseDialog::SetSelfTestResult(bool camera, bool laser, bool battery, bool storage)
{
    m_isCamera = camera;
    m_isLaser = laser;
    m_isBattery = battery;
    m_isStorage = storage;
}

void BaseDialog::setSize(QSize size)
{
//    ui->verticalLayout->itemAt(0)->widget()->resize(GetWidgetSize(QSize(size.width(), 130)));
//    ui->titleLabel->resize(GetWidgetSize(QSize(size.width(), 130)));
//    ui->verticalLayout->itemAt(1)->widget()->resize(GetWidgetSize(QSize(size.width(), size.height() - 130)));
    QSize changedSize = GetWidgetSize(size);
    this->setFixedSize(changedSize);
    ui->verticalLayout->setStretch(0, 130);
    ui->verticalLayout->setStretch(1, size.height() - 130);

    if (m_bIsCloseButton)
    {
        int height = (130);
        int gap = GetCalcGap(5);
        m_pClosePushButton->setGeometry(GetWidgetSizePos(QRect(QPoint(size.width() - 130 + gap, gap), QSize(height - gap * 2, height - gap * 2))));
    }
//    ui->titleLabel->resize(GetWidgetSize(QSize(size.width(), 130)));
}

void BaseDialog::setSize(int w, int h)
{
//    ui->verticalLayout->itemAt(0)->widget()->resize(GetWidgetSize(QSize(w, 130)));
//    ui->verticalLayout->itemAt(1)->widget()->resize(GetWidgetSize(QSize(w, h - 130)));
    QSize size = GetWidgetSize(QSize(w, h));
    this->setFixedSize(size);
    ui->verticalLayout->setStretch(0, 130);
    ui->verticalLayout->setStretch(1, h - 130);

    if (m_bIsCloseButton)
    {

        QRect rect = this->geometry();
//        rect.setSize(QSize(rect.width(), 130));
//        rect.setWidth(rect.width()-130);
//        rect.height();
//        int height = 130 / rect.height();
//        QRect height3 = ui->verticalLayout_3->itemAt(0)->geometry();
//        int height = rect.height() * ui->verticalLayout->stretch(0) / (ui->verticalLayout->stretch(0) + ui->verticalLayout->stretch(1));
        int height = (130);
        int gap = GetCalcGap(5);
        m_pClosePushButton->setGeometry(GetWidgetSizePos(QRect(QPoint(w - 130 + gap, gap), QSize(height - gap * 2, height - gap * 2))));
    }
    //    ui->titleLabel->resize(GetWidgetSize(QSize(w, 130)));
}

void BaseDialog::drawBorder(QRect rect)
{
}

QWidget *BaseDialog::pWidget() const
{
    return ui->verticalLayout->itemAt(1)->widget();
//    return ui->verticalLayout->widget();
}



void BaseDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(127,127,127)));
    QRect rect = ui->verticalLayout->itemAt(0)->geometry();
    painter.drawLine(rect.bottomLeft(), rect.bottomRight());


}

void BaseDialog::resizeEvent(QResizeEvent *event)
{
//    QPainter painter(this);
//    QStyleOptionFrame  option;
//    option.initFrom(this);
//    option.rect = this->geometry().adjusted(1, 1, -1, -1);
//    option.lineWidth = 1;
//    option.frameShape = QFrame::Box;
//    style()->drawPrimitive(QStyle::PE_Frame,  &option,  &painter,  this);

//    QPainter painter(this);
//    painter.setPen(QPen(QColor(Qt::black)));
//    painter.drawRect(rect());

    if (m_bIsCloseButton)
    {

        QRect rect = this->geometry();
//        rect.setSize(QSize(rect.width(), 130));
//        rect.setWidth(rect.width()-130);
//        rect.height();
//        int height = 130 / rect.height();
//        QRect height3 = ui->verticalLayout_3->itemAt(0)->geometry();
//        int height = rect.height() * ui->verticalLayout->stretch(0) / (ui->verticalLayout->stretch(0) + ui->verticalLayout->stretch(1));
//        int height = GetWidthHeight(130);
//        m_pClosePushButton->setGeometry(QRect(QPoint(rect.width() - height - 5, 5), QSize(height - 10, height - 10)));
//        ui->horizontalLayout->setStretch(0, rect.width() - width);
//        ui->horizontalLayout->setStretch(1, width);
//        ui->horizontalLayout->setStretch(0, width);
//        ui->horizontalLayout->setStretch(1, ui->horizontalLayout->geometry().size().width() - width);
//        ui->closePushButton->resize(width - 10, width - 10);
//        int width = ui->horizontalLayout->geometry().adjusted(1,1,-1,-1).size().width();
//        ui->closePushButton->setGeometry(QRect(geometry().width() - width - 1, 1, width, width));
    }
}

void BaseDialog::on_closePushButton_clicked()
{
    accept();
}

void BaseDialog::changeConnectingState(bool isConnecting)
{
    if(isConnecting)
    {
        ui->connectingStateLabel->setText(LoadString("IDS_WIFI_FINDING"));
        QCoreApplication::processEvents();
        emit sig_searchingWIFIDone();
    }
    else
        ui->connectingStateLabel->setText("");
}
