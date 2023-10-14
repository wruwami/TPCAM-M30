#include "AdminPWWidget.h"
#include "ui_AdminPWWidget.h"

#include <QDialog>

#include "StringLoader.h"
#include "ConfigManager.h"

AdminPWWidget::AdminPWWidget(QString msg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPWWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;

    if (!msg.isEmpty())
    {
        ui->label->setText(msg);
        ui->label->setText(msg);
    }
    ui->pwLabel->setText(LoadString("IDS_PW"));
    ui->pwLabel->setFontSize(23);

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->okPushButton->setFontSize(23);
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->cancelPushButton->setFontSize(23);
}

AdminPWWidget::~AdminPWWidget()
{
    delete ui;
}

void AdminPWWidget::on_okPushButton_clicked()
{
    ConfigManager config = ConfigManager("setting_password.json");
    QJsonObject object = config.GetConfig();
    if (object["password"].toString() == ui->lineEdit->GetString())
    {
        m_pParent->accept();
    }
}

void AdminPWWidget::on_cancelPushButton_clicked()
{
    m_pParent->reject();
}
