#include "Setting6Widget.h"
#include "ui_Setting6Widget.h"

#include <QJsonArray>

#include "StringLoader.h"
#include "BaseDialog.h"

Setting6Widget::Setting6Widget(QWidget *parent) : QWidget(parent),
    ui(new Ui::Setting6Widget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;

    ui->languageLabel->setText(LoadString("IDS_LANUAGE"));
    ui->bludtoothLabel->setText(LoadString("IDS_BLUETOOTH"));
    ui->ftpLabel->setText(LoadString("IDS_FTP"));

    ui->searchPushButton->setText(LoadString("IDS_SEARCH"));

    ui->languageComboBox->addItems(LoadLangaugeList());

    ui->ftpComboBox->addItem(LoadString("IDS_DISABLE"));
    ui->ftpComboBox->addItem(LoadString("IDS_ENABLE_AUTO"));
    ui->ftpComboBox->addItem(LoadString("IDS_ENABLE_MANUAL"));

//    ui->languageComboBox->addItems(LoadLangaugeList());
    foreach (QJsonValue json, m_jsonObject["language items"].toArray())
    {
        ui->languageComboBox->addItem(json.toString());
    }
    int index = m_jsonObject["language selection"].toInt();
    ui->languageComboBox->setCurrentIndex(index - 1);

    ui->ftpPortLineEdit->setText(LoadString("IDS_PORT"));
    ui->userNameLineEdit->setText(LoadString("IDS_USER_NAME"));
    ui->userPassLineEdit->setText(LoadString("IDS_USER_PASS"));

    ui->ftpPortLineEdit->SetMode(Mode::KeypadType);

    foreach (QJsonValue json, m_jsonObject["bluetooth items"].toArray())
    {
        ui->bluetoothComboBox->addItem(json.toString());
    }
    index = m_jsonObject["bluetooth selection"].toInt();
    ui->bluetoothComboBox->setCurrentIndex(index - 1);

    foreach (QJsonValue json, m_jsonObject["ftp items"].toArray())
    {
        ui->ftpComboBox->addItem(json.toString());
    }
    index = m_jsonObject["ftp select"].toInt();
    ui->ftpComboBox->setCurrentIndex(index - 1);

    ui->ftpAddressLineEdit->setText(m_jsonObject["ftp server(dns)"].toString());
    ui->ftpPortLineEdit->setText(m_jsonObject["ftp port"].toString());
    ui->userNameLineEdit->setText(m_jsonObject["ftp user name"].toString());
    ui->userPassLineEdit->setText(m_jsonObject["ftp password"].toString());
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

void Setting6Widget::on_languageComboBox_currentIndexChanged(const QString &arg1)
{
    ResourceLoader::StringLoader::GetInstance()->Initialize("strings", "stringTable.csv", arg1.toStdString());

}
