#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ConfigManager
{
public:
    ConfigManager(QString file_name);
    QJsonObject GetConfig();
    void SetConfig(QJsonObject);
    QString GetText();
    void SaveFile();
private:
    QJsonDocument m_jsonDocument;
    QString m_file_full_path;
    QString m_text;
};

#endif // CONFIGMANAGER_H
