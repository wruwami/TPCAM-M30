#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

class ConfigManager
{
public:
    ConfigManager(QString file_name);
    QJsonObject GetConfig();
    void SetConfig(QJsonObject);

    void SaveFile();
private:
    QJsonDocument m_jsonDocument;
    QString m_file_full_path;
};

#endif // CONFIGMANAGER_H
