/**
 * @file DateFormatManager.h
 * @author wruwami (wruwami@naver.com)
 * @brief 날짜 포맷을 관리하는 클래스, 설정은 세팅 3에서 수행한다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DATEFORMATMANAGER_H
#define DATEFORMATMANAGER_H

#include <QString>

enum DateFormat
{
    YYYYMMDD = 0,
    MMDDYYYY = 1,
    DDMMYYYY = 2,
};

namespace ResourceLoader{
class DateFormatManager
{
private:
    DateFormatManager();
    DateFormatManager(const DateFormatManager& other);
    ~DateFormatManager() {}
    static DateFormatManager* instance;
public:
    static DateFormatManager* GetInstance()
    {
        if(instance == nullptr) instance = new DateFormatManager();
        return instance;
    }
    void SetDateFormat(DateFormat);
    DateFormat GetDateFormat();
    QString GetDate(QString str);
private:
    DateFormat m_DateFormat;
};
}

static void SetDateFormat(DateFormat dateFormat)
{
    ResourceLoader::DateFormatManager::GetInstance()->SetDateFormat(dateFormat);
}

static DateFormat GetDateFormat()
{
    return ResourceLoader::DateFormatManager::GetInstance()->GetDateFormat();
}

static QString GetDate(QString str)
{
    return ResourceLoader::DateFormatManager::GetInstance()->GetDate(str);
}

#endif // DATEFORMATMANAGER_H
