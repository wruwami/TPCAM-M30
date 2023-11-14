#include "Setting4APWidget.h"
#include "ui_Setting4APWidget.h"

#include "StringLoader.h"

#include "BaseDialog.h"
#include "NetworkManager.h"
#include "PasswordChangingWidget.h"

Setting4APWidget::Setting4APWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting4APWidget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;

    ui->macAddressLabel->setText(LoadString("IDS_MAC_ADDRESS"));
    ui->macAddressLabel->setFontSize(23);
    ui->wifiSSIDnFTPIDlabel->setText(LoadString("IDS_WIFISSID_AND_FTP_ID"));
    ui->wifiSSIDnFTPIDlabel->setFontSize(23);
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->IpLabel->setFontSize(23);
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->subnetMaskLabel->setFontSize(23);
    ui->printerLabel->setText(LoadString("IDS_PRINTER"));
    ui->printerLabel->setFontSize(23);

    foreach (QJsonValue json, m_jsonObject["printer items"].toArray())
    {
        ui->printerComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    int index = m_jsonObject["printer selection"].toInt() - 1;
    ui->printerComboBox->setCurrentIndex(index);

    ui->pwPushButton->setText(LoadString("IDS_PW"));
    ui->pwPushButton->setFontSize(23);

    ui->macAddressLineEdit->setDisabled(true);
    NetworkManager networkManager;
    ui->macAddressLineEdit->setText(networkManager.getHardwareAddress(networkManager.getWlanAdapterName()));
    ui->ipLineEdit->SetMode(Mode::KeypadType);
    ui->macAddressLineEdit->SetMode(Mode::KeyboardType);

//    ui->macAddressLineEdit->setText(m_jsonObject["mac address"].toString());
//    NetworkManager networkManager;
//    networkManager.getWlanAdapterName();
    ui->wifiSSIDnFTPlineEdit->setText(m_jsonObject["wiFi SSID"].toString());
    ui->ipLineEdit->setText(m_jsonObject["ip"].toString());
    ui->subnetMaskLineEdit->setText(m_jsonObject["subnet mask"].toString());
}

Setting4APWidget::~Setting4APWidget()
{

    delete ui;
}

void Setting4APWidget::SaveConfig()
{
    m_config.SetConfig(m_newJsonObject);
    m_config.SaveFile();

}

void Setting4APWidget::on_pwPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::NetworkPasswordChangingWidgetType, Qt::AlignmentFlag::AlignCenter, "", false, LoadString("IDS_NETWORK_PASSWORD"));
    connect((PasswordChangingWidget*)baseDialog.pWidget(), SIGNAL(sig_sendPW(QString)), this, SLOT(on_sendPW(QString)));
    if (baseDialog.exec() == QDialog::Accepted)
    {
        ConfigManager config = ConfigManager("setting_password.json");
        QJsonObject object = config.GetConfig();
        object["network password"] = m_strNewPassword;
        config.SetConfig(object);
        config.SaveFile();
    }
//    connect((PasswordChanging)baseDialog.pWidget(), SIGNAL())

}

void Setting4APWidget::on_wifiSSIDnFTPlineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["wiFi SSID"] = arg1;
}

void Setting4APWidget::on_ipLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["ip"] = arg1;
}

void Setting4APWidget::on_subnetMaskLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["subnet mask"] = arg1;
}

void Setting4APWidget::on_printerComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["printer selection"] = index + 1;
}

void Setting4APWidget::on_sendPW(QString pw)
{
    m_strNewPassword = pw;
}
