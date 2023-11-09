#include "DateFormatManager.h"

#include "ConfigManager.h"

using namespace ResourceLoader;
DateFormatManager* DateFormatManager::instance = nullptr;

DateFormatManager::DateFormatManager()
{
    ConfigManager config = ConfigManager("parameter_setting3.json");
    QJsonObject object = config.GetConfig();
    switch(object["date format selection"].toInt() - 1)
    {
    case 0:
    {
        m_DateFormat = YYYYMMDD;
    }
        break;
    case 1:
    {
        m_DateFormat = MMDDYYYY;
    }
        break;
    case 2:
    {
        m_DateFormat = DDMMYYYY;
    }
        break;

    }
}

void DateFormatManager::SetDateFormat(DateFormat dateFormat)
{
    m_DateFormat = dateFormat;
}

DateFormat DateFormatManager::GetDateFormat()
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
