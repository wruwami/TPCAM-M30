#include "DateFormatManager.h"

#include "ConfigManager.h"

using namespace ResourceLoader;
DateFormatManager* DateFormatManager::instance = nullptr;

DateFormatManager::DateFormatManager()
{
    ConfigManager config = ConfigManager("parameter_setting3.json");
    QJsonObject object = config.GetConfig();
    m_DateFormat = object["date format items"].toArray()[object["date format selection"].toInt() - 1].toString();
}

void DateFormatManager::SetDateFormat(QString dateFormat)
{
    m_DateFormat = dateFormat;
}

QString DateFormatManager::GetDateFormat()
{
    return m_DateFormat;
}

QString DateFormatManager::GetDate(QString str)
{
    if (m_DateFormat == "YYYY/MM/DD")
    {
        return str.mid(0,4) + "/" +str.mid(4,2) + "/" +str.mid(6,2);
    }
    else if (m_DateFormat == "MM/DD/YYYY")
    {
        return str.mid(4,2) + "/" +str.mid(6,2) + "/" +str.mid(0,4);
    }
    else if (m_DateFormat == "DD/MM/YYYY")
    {
        return str.mid(6,2) + "/" +str.mid(4,2) + "/" +str.mid(0,4);
    }
}
