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

void DateFormatManager::SetDateFormat(DateFormat dateFormat)
{
    m_DateFormat = dateFormat;
}

QString DateFormatManager::GetDateFormat()
{
    return m_DateFormat;
}

QString DateFormatManager::GetDate(QString str)
{
    if (m_DateFormat == YYYYMMDD)
    {
        return str.mid(0,4) + "/" +str.mid(4,2) + "/" +str.mid(6,2);
    }
    else if (m_DateFormat == MMDDYYYY)
    {
        return str.mid(4,2) + "/" +str.mid(6,2) + "/" +str.mid(0,4);
    }
    else if (m_DateFormat == DDMMYYYY)
    {
        return str.mid(6,2) + "/" +str.mid(4,2) + "/" +str.mid(0,4);
    }
}
