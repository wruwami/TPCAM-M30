#include "FactoryDefaultWidget.h"
#include "ui_FactoryDefaultWidget.h"

#include <QDialog>
#include <QJsonObject>
#include "qdir.h"

#include "StringLoader.h"
#include "ConfigManager.h"
#include "FileManager.h"

FactoryDefaultWidget::FactoryDefaultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FactoryDefaultWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;
    ui->factoryDefaultLabel->setText(LoadString("IDS_ARE_U_SURE_FACTORY_DEFAULT"));
    ui->pwLabel->setText(LoadString("IDS_PW"));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
}

FactoryDefaultWidget::~FactoryDefaultWidget()
{
    delete ui;
}

void FactoryDefaultWidget::MoveFactorySetting()
{
//    QDir dir = GeteMMCPath()

}

void FactoryDefaultWidget::on_okPushButton_clicked()
{
    ConfigManager config = ConfigManager("setting_password.json");
    QJsonObject object = config.GetConfig();
    if (object["password"].toString() == ui->lineEdit->GetString())
    {
        MoveFactorySetting();
        m_pParent->accept();
    }
}

void FactoryDefaultWidget::on_cancelPushButton_clicked()
{
    m_pParent->reject();
}
