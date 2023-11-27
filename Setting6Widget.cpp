#include "Setting6Widget.h"
#include "ui_Setting6Widget.h"

#include "regex"

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
    ui->languageLabel->setFontSize(23);
    ui->bludtoothLabel->setText(LoadString("IDS_BLUETOOTH"));
    ui->bludtoothLabel->setFontSize(23);
    ui->ftpLabel->setText(LoadString("IDS_FTP"));
    ui->ftpLabel->setFontSize(23);

    ui->searchPushButton->setText(LoadString("IDS_SEARCH"));
    ui->searchPushButton->setFontSize(23);

//    ui->languageComboBox->addItems(LoadLangaugeList());

//    ui->ftpComboBox->addItem(LoadString("IDS_DISABLE"));
//    ui->ftpComboBox->addItem(LoadString("IDS_ENABLE_AUTO"));
//    ui->ftpComboBox->addItem(LoadString("IDS_ENABLE_MANUAL"));

//    ui->languageComboBox->addItems(LoadLangaugeList());
    foreach (QJsonValue json, m_jsonObject["language items"].toArray())
    {
        ui->languageComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    int index = m_jsonObject["language select"].toInt();
    ui->languageComboBox->setCurrentIndex(index - 1);

    ui->ftpPortLineEdit->setText(LoadString("IDS_PORT"));
    ui->userNameLineEdit->setText(LoadString("IDS_USER_NAME"));
    ui->userPassLineEdit->setText(LoadString("IDS_USER_PASS"));

    ui->ftpPortLineEdit->SetMode(Mode::KeypadType);

    foreach (QJsonValue json, m_jsonObject["bluetooth items"].toArray())
    {
        ui->bluetoothComboBox->addItem(json.toString());
    }
    index = m_jsonObject["bluetooth select"].toInt();
    ui->bluetoothComboBox->setCurrentIndex(index - 1);

    foreach (QJsonValue json, m_jsonObject["ftp items"].toArray())
    {
        ui->ftpComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    index = m_jsonObject["ftp select"].toInt();
    ui->ftpComboBox->setCurrentIndex(index - 1);

    ui->ftpAddressLineEdit->setText(m_jsonObject["ftp server( dns )"].toString());
    ui->ftpAddressLineEdit->setAlignment(Qt::AlignLeft);
    ui->ftpPortLineEdit->setText(QString::number(m_jsonObject["ftp port"].toInt()));
    ui->ftpPortLineEdit->setAlignment(Qt::AlignLeft);
    ui->userNameLineEdit->setText(m_jsonObject["ftp user name"].toString());
    ui->userNameLineEdit->setAlignment(Qt::AlignLeft);
    ui->userPassLineEdit->setText(m_jsonObject["ftp password"].toString());
    ui->userPassLineEdit->setAlignment(Qt::AlignLeft);

    //BT disable
    ui->bluetoothComboBox->setEnabled(false);
    ui->searchPushButton->setEnabled(false);
    ui->bludtoothLabel->setEnabled(false);

    connect(ui->ftpAddressLineEdit, SIGNAL(sig_text(QString)), this, SLOT(on_text(QString)));
}

Setting6Widget::~Setting6Widget()
{
    delete ui;
}

void Setting6Widget::SaveConfig()
{
    m_config.SetConfig(m_newJsonObject);
    m_config.SaveFile();

}

void Setting6Widget::on_searchPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::BluetoothSearchFilterWidgetType, Qt::AlignmentFlag::AlignCenter, "");
    baseDialog.exec();
}

void Setting6Widget::on_languageComboBox_currentIndexChanged(const QString &arg1)
{
//    ResourceLoader::StringLoader::GetInstance()->Initialize("strings", "stringTable.csv", arg1.toStdString());

}

void Setting6Widget::on_languageComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["language select"] = index + 1;
//    ResourceLoader::StringLoader::GetInstance()->Initialize("strings", "stringTable.csv", m_jsonObject["start language items"].toArray()[index].toString().toStdString());
}

void Setting6Widget::on_bluetoothComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["bluetooth select"] = index + 1;
}

void Setting6Widget::on_ftpComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["ftp select"] = index + 1;

    if (index == 0)
    {
        ui->ftpAddressLineEdit->setDisabled(true);
        ui->ftpPortLineEdit->setDisabled(true);
        ui->userNameLineEdit->setDisabled(true);
        ui->userPassLineEdit->setDisabled(true);
    }
    else
    {
        ui->ftpAddressLineEdit->setDisabled(false);
        ui->ftpPortLineEdit->setDisabled(false);
        ui->userNameLineEdit->setDisabled(false);
        ui->userPassLineEdit->setDisabled(false);
    }
}

void Setting6Widget::on_ftpPortLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["ftp port"] = arg1.toInt();
}

void Setting6Widget::on_userNameLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["ftp user name"] = arg1;
}

void Setting6Widget::on_userPassLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["ftp password"] = arg1;
}

void Setting6Widget::initializeStringTable()
{
    ResourceLoader::StringLoader::GetInstance()->Initialize("strings", "stringTable.csv", m_jsonObject["start language items"].toArray()[ui->languageComboBox->currentIndex()].toString().toStdString());
}

void Setting6Widget::on_text(QString arg1)
{
//    std::regex re("^((http[s]?|ftp):\\/)?\\/?([^:\\/\\s]+)((\\/\\w+)*\\/)([\\w\\-\\.]+[^#?\\s]+)(.*)?(#[\\w\\-]+)?$");
    std::regex re("[-a-zA-Z0-9@:%._\\+~#=]{1,256}\\.[a-zA-Z0-9()]{1,6}");
    std::smatch match;
    std::string str = arg1.toStdString();
    if (std::regex_search(str, match, re))
    {
        ui->ftpAddressLineEdit->setText(QString(match.str().c_str())); m_newJsonObject["ftp server( dns )"] = QString(match.str().c_str());
    }
    else
    {
        ui->ftpAddressLineEdit->clear();

    }
}

