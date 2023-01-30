#include "DateFormatManager.h"

DateFormatManager* DateFormatManager::instance = nullptr;

void DateFormatManager::SetDateFormat(QString dateFormat)
{
    m_DateFormat = dateFormat;
}

QString DateFormatManager::GetDateFormat()
{
    m_DateFormat;
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
