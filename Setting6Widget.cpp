#include "Setting6Widget.h"
#include "ui_Setting6Widget.h"

#include "StringLoader.h"
#include "BaseDialog.h"

Setting6Widget::Setting6Widget(QWidget *parent) : QWidget(parent),
    ui(new Ui::Setting6Widget)
{
    ui->setupUi(this);

    ui->languageLabel->setText(LoadString("IDS_LANUAGE"));
    ui->bludtoothLabel->setText(LoadString("IDS_BLUETOOTH"));
    ui->ftpLabel->setText(LoadString("IDS_FTP"));

    ui->searchPushButton->setText(LoadString("IDS_SEARCH"));

    ui->languageComboBox->addItems(LoadLangaugeList());

    ui->ftpComboBox->addItem(LoadString("IDS_DISABLE"));
    ui->ftpComboBox->addItem(LoadString("IDS_ENABLE_AUTO"));
    ui->ftpComboBox->addItem(LoadString("IDS_ENABLE_MANUAL"));

    ui->languageComboBox->addItems(LoadLangaugeList());

    ui->ftpAddressLineEdit->setText("ftp://comlaser.xxxx.xxx");
    ui->ftpPortLineEdit->setText(LoadString("IDS_PORT"));
    ui->userNameLineEdit->setText(LoadString("IDS_USER_NAME"));
    ui->userPassLineEdit->setText(LoadString("IDS_USER_PASS"));
}

Setting6Widget::~Setting6Widget()
{
    delete ui;
}

void Setting6Widget::on_searchPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::BluetoothSearchFilterWidgetType, Qt::AlignmentFlag::AlignCenter);
    baseDialog.exec();
}
