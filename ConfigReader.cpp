#include "ConfigReader.h"

#include <QDebug>
#include <QFile>
#include <QJsonParseError>

ConfigReader::ConfigReader(QString file_name)
{
    QFile file(file_name);
    file.open(QFile::ReadWrite);

    if (!file.isOpen())
    {
        qDebug() << "no file has been opened";
        file.close();
        return;
    }

    QByteArray json = file.readAll();
    QJsonParseError error{};
    m_jsonObject = QJsonDocument::fromJson(json, &error).object();
    file.close();
}

QJsonObject ConfigReader::GetConfig()
{
    return m_jsonObject;
}

void ConfigReader::SetConfig(QJsonObject jsonObject)
{
    m_jsonObject = jsonObject;
}

