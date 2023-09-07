#include "FactoryDefaultWidget.h"
#include "ui_FactoryDefaultWidget.h"

#include <QDialog>
#include <QJsonObject>
#include "qdir.h"
#include <QDebug>

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
    ui->factoryDefaultLabel->setFontSize(23);
    ui->pwLabel->setText(LoadString("IDS_PW"));
    ui->pwLabel->setFontSize(23);

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->okPushButton->setFontSize(23);
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->cancelPushButton->setFontSize(23);
}

FactoryDefaultWidget::~FactoryDefaultWidget()
{
    delete ui;
}

void FactoryDefaultWidget::MoveFactorySetting()
{
    QDir dir = GeteMMCPath() + "/settings";

    foreach (QFileInfo item, dir.entryInfoList())
    {
//        qDebug() << item.fileName();
//        qDebug() << GeteMMCPath() + "/settings/factory/" +item.fileName();
//        qDebug() << GeteMMCPath() + "/settings/" + item.fileName();
        if (item.fileName() == "." || item.fileName() == "..")
            continue;

        if (QFile::exists(GeteMMCPath() + "/settings/" + item.fileName()))
        {
            QFile::remove(GeteMMCPath() + "/settings/" + item.fileName());
        }

        QFile::copy(GeteMMCPath() + "/settings/factory/" +item.fileName(), GeteMMCPath() + "/settings/" + item.fileName());
    }
}

void FactoryDefaultWidget::on_okPushButton_clicked()
{
    ConfigManager config = ConfigManager("setting_password.json");
    QJsonObject object = config.GetConfig();
    if (object["password"].toString() == ui->lineEdit->GetString())
    {
//        MoveFactorySetting();
        m_pParent->accept();
    }
}

void FactoryDefaultWidget::on_cancelPushButton_clicked()
{
    m_pParent->reject();
}
