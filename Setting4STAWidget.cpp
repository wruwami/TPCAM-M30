#include "Setting4STAWidget.h"
#include "ui_Setting4STAWidget.h"

#include <QJsonArray>

#include "StringLoader.h"
#include "BaseDialog.h"
#include "KeyboardDialog.h"

#include "NetworkManager.h"
#include "WifiSearchWidget.h"
#include "PasswordChangingWidget.h"

Setting4STAWidget::Setting4STAWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting4STAWidget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;
    m_passwordjsonObject = m_config.GetConfig();

    ui->searchPushButton->setText(LoadString("IDS_SEARCH"));
    ui->searchPushButton->setFontSize(23);
    ui->wifiSSIDLabel->setText(LoadString("IDS_WIFI_SSID"));
    ui->wifiSSIDLabel->setFontSize(23);
    ui->FTPIDPWLabel->setText(LoadString("IDS_FTP_ID_PW"));
    ui->FTPIDPWLabel->setFontSize(23);
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->IpLabel->setFontSize(23);
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->subnetMaskLabel->setFontSize(23);
    ui->printerLabel->setText(LoadString("IDS_PRINTER"));
    ui->printerLabel->setFontSize(23);
    ui->pwPushButton->setText(LoadString("IDS_PW"));
    ui->pwPushButton->setFontSize(23);

//    ui->printerComboBox->addItem(LoadString("IDS_THERMAL_EAST"));
//    ui->printerComboBox->addItem(LoadString("IDS_THERMAL_WOOSIM"));
//    ui->printerComboBox->addItem(LoadString("IDS_BT_HP"));

    QJsonArray ar = m_jsonObject["sta ssid"].toArray();
    foreach(auto item, ar)
    {
        ui->wifiSSIDComboBox->addItem(item.toString());
    }

    ui->wifiSSIDComboBox->setCurrentIndex(0);


    foreach (QJsonValue json, m_jsonObject["printer items"].toArray())
    {
        ui->printerComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    int index = m_jsonObject["printer selection"].toInt() - 1;
    ui->printerComboBox->setCurrentIndex(index);

    ui->FTPIDPWLineEdit->setText(m_jsonObject["sta ftp id & p/w"].toString());

    NetworkManager netWorkManager;
    if (netWorkManager.getWlanAdapterName().isEmpty())
    {
        ui->searchPushButton->setDisabled(true);
    }


    NetworkManager networkManager;
    QNetworkInterface eth1Ip = QNetworkInterface::interfaceFromName(networkManager.getWlanAdapterName());
    QList<QNetworkAddressEntry> entries = eth1Ip.addressEntries();
    if (!entries.isEmpty()) {
        QNetworkAddressEntry entry = entries.first();

        qDebug() << "getIP.length : " << entry.ip().toString().length();

        if ( entry.ip().toString().length()< 16) {
             ui->ipLineEdit->setText(entry.ip().toString());
        } else {
             ui->ipLineEdit->setText("");
        }

	    ui->subnetMaskLineEdit->setText(networkManager.GetSubNetMask( entry.ip().toString() ));
    }

//	ui->ipLineEdit->setText(m_jsonObject["ip"].toString());
	ui->ipLineEdit->setDisabled(true);
	ui->subnetMaskLineEdit->setDisabled(true);

    ui->IpLabel->setDisabled(true);
    ui->subnetMaskLabel->setDisabled(true);
}

Setting4STAWidget::~Setting4STAWidget()
{
    delete ui;
}

void Setting4STAWidget::SaveConfig()
{
    if (m_bSearching)
    {
        QJsonArray ar = m_jsonObject["sta ssid"].toArray();
        QJsonValue jv = ar[m_nSSIDIndex];
        ar.removeAt(m_nSSIDIndex);
        ar.insert(0, jv);
        m_newJsonObject["sta ssid selection"] = ui->wifiSSIDComboBox->currentIndex() + 1;
        m_newJsonObject["sta ssid"] = ar;
    }

    m_config.SaveFile();
    m_config.SetConfig(m_newJsonObject);
    m_config.SaveFile();

}

void Setting4STAWidget::on_pwPushButton_clicked()
{
//    KeyboardDialog keyboardDialog(GetLanguage());
//    if (keyboardDialog.exec() == QDialog::Accepted)
//    {
//        m_passwordjsonObject["network password"] = keyboardDialog.str();
//    }
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
}

void Setting4STAWidget::on_FTPIDPWLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["sta ftp id & p/w"] = arg1;
}

void Setting4STAWidget::on_ipLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["ip"] = arg1;
}

void Setting4STAWidget::on_subnetMaskLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["subnet mask"] = arg1;
}

void Setting4STAWidget::on_printerComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["printer selection"] = index + 1;
}


void Setting4STAWidget::on_searchPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::WifiSearchWidgetType, Qt::AlignmentFlag::AlignLeft);
//    WifiSearchWidget* wifiSearchWidget = ();
    connect((WifiSearchWidget*)baseDialog.pWidget(), SIGNAL(sig_sendSSID(QString)), this, SLOT(on_sendSSID(QString)));
    if (baseDialog.exec() == QDialog::Accepted)
    {
        m_bSearching = true;
    }
    else
    {
        m_bSearching = false;
    }

}

int Setting4STAWidget::CheckComboxBoxItem(QString str)
{
    for (int i = 0 ; i < ui->wifiSSIDComboBox->count() ; i++)
    {
        if ( str  == ui->wifiSSIDComboBox->itemText(i))
            return i;
    }

    return -1;
}

void Setting4STAWidget::on_sendSSID(QString strSSID)
{

    int index = -1;
    if ((index = CheckComboxBoxItem(strSSID)) == -1)
    {
        ui->wifiSSIDComboBox->removeItem(4);
        ui->wifiSSIDComboBox->insertItem(0, strSSID);
    }
    else
    {
        ui->wifiSSIDComboBox->removeItem(index);
        ui->wifiSSIDComboBox->insertItem(0, strSSID);
    }

//    ui->wifiSSIDComboBox->removeItem(4);
//    ui->wifiSSIDComboBox->insertItem(0, strSSID);

    QJsonArray array = m_jsonObject["sta ssid"].toArray();
    while(array.count()) {
        array.pop_back();
    }
    for (int i = 0 ; i < ui->wifiSSIDComboBox->count() ; i++)
    {
        array.push_back(ui->wifiSSIDComboBox->itemText(i));
    }
    m_jsonObject["sta ssid"] = array;
    m_newJsonObject["sta ssid"] = m_jsonObject["sta ssid"];

    ui->wifiSSIDComboBox->setCurrentIndex(0);
}

void Setting4STAWidget::on_sendPW(QString pw)
{
    m_strNewPassword = pw;
}


void Setting4STAWidget::on_wifiSSIDComboBox_currentIndexChanged(int index)
{
    m_nSSIDIndex = index;
}

