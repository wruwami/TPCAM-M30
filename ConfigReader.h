#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QString>
#include <QJsonObject>

class ConfigReader
{
public:
    ConfigReader(QString file_name);
    QJsonObject GetConfig();
    void SetConfig(QJsonObject);
private:
    QJsonObject m_jsonObject;
};

#endif // CONFIGREADER_H
