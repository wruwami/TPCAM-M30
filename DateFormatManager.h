#ifndef DATEFORMATMANAGER_H
#define DATEFORMATMANAGER_H

#include <QString>

//enum DateFormat
//{
//    YYYYMMDD,
//    MMDDYYYY,
//    DDMMYYYY,
//    MMMDDYYY,
//};

namespace ResourceLoader{
class DateFormatManager
{
private:
    DateFormatManager() {}
    DateFormatManager(const DateFormatManager& other);
    ~DateFormatManager() {}
    static DateFormatManager* instance;
public:
    static DateFormatManager* GetInstance()
    {
        if(instance == nullptr) instance = new DateFormatManager();
        return instance;
    }
    void SetDateFormat(QString);
    QString GetDateFormat();
    QString GetDate(QString str);
private:
    QString m_DateFormat;
};
}

static void SetDateFormat(QString dateFormat)
{
    ResourceLoader::DateFormatManager::GetInstance()->SetDateFormat(dateFormat);
}

static QString GetDateFormat()
{
    return ResourceLoader::DateFormatManager::GetInstance()->GetDateFormat();
}

static QString GetDate(QString str)
{
    return ResourceLoader::DateFormatManager::GetInstance()->GetDate(str);
}

#endif // DATEFORMATMANAGER_H
