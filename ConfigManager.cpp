#include "ConfigManager.h"

#include "qdir.h"
#include <QDebug>
#include <QFile>
#include <QJsonParseError>

#define DEFAULT_PATH    "settings"

ConfigManager::ConfigManager(QString file_name)
{
    QDir qdir;

    m_file_full_path = qdir.absolutePath() + "/" + DEFAULT_PATH + "/" + file_name;

    QFile file(m_file_full_path);
    file.open(QFile::ReadWrite);

    if (!file.isOpen())
    {
        qDebug() << "no file has been opened";
        file.close();
        return;
    }

    QByteArray qa = file.readAll();
    QJsonParseError error{};
    m_text = QString(qa);
    m_jsonDocument = QJsonDocument::fromJson(qa, &error);
    file.close();
}

QJsonObject ConfigManager::GetConfig()
{
    return m_jsonDocument.object();
}

void ConfigManager::SetConfig(QJsonObject jsonObject)
{
    m_jsonDocument = QJsonDocument(jsonObject);
}

QString ConfigManager::GetText()
{
    return m_text;
}

void ConfigManager::SaveFile()
{
    QFile file(m_file_full_path);
    file.open(QFile::WriteOnly);

    file.write(m_jsonDocument.toJson());
    file.close();
}
