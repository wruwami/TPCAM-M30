#include "PasswordChangingWidget.h"
#include "ui_PasswordChangingWidget.h"

#include "StringLoader.h"
#include "ConfigManager.h"

#include <QDialog>

PasswordChangingWidget::PasswordChangingWidget(bool bNetwork, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordChangingWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;

    m_bNetwork = bNetwork;
    if (m_bNetwork)
    {
        QString password = ConfigManager("setting_password.json").GetConfig()["network password"].toString();
        ui->currentLineEdit->setText(password);
        ui->currentLineEdit->setDisabled(true);
    }
    ui->currentLabel->setText(LoadString("IDS_CURRENT"));
    ui->newLabel->setText(LoadString("IDS_NEW"));
    ui->confirmLabel->setText(LoadString("IDS_CONFIRM"));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
}

PasswordChangingWidget::~PasswordChangingWidget()
{
    delete ui;
}

void PasswordChangingWidget::on_okPushButton_clicked()
{
    ConfigManager config = ConfigManager("setting_password.json");
    QJsonObject object = config.GetConfig();

    QString password;
    if (m_bNetwork)
    {
        password = object["network password"].toString();
    }
    else
    {
        password = object["password"].toString();

    }
    if (password != ui->currentLineEdit->GetString())
        return;

    if (ui->newLineEdit->GetString().isEmpty() && (ui->currentLineEdit->GetString().isEmpty()))
        return;

    if (ui->newLineEdit->GetString() == ui->currentLineEdit->GetString())
        return;

    emit sig_sendPW(ui->newLineEdit->GetString());
//    object["password"] = ui->newLineEdit->GetString();
//    config.SetConfig(object);
//    config.SaveFile();
    m_pParent->accept();
}

void PasswordChangingWidget::on_cancelPushButton_clicked()
{
    m_pParent->reject();
}
