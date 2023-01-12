#ifndef STRINGLOADER_H
#define STRINGLOADER_H


#include <map>
#include <QString>
#include <QStringList>
#include <list>
#include <string>

namespace ResourceLoader{
class StringLoader
{
private:
    StringLoader() {}
    StringLoader(const StringLoader& other);
    ~StringLoader() {}
    static StringLoader* instance;
public:
    static StringLoader* GetInstance()
    {
        if(instance == nullptr) instance = new StringLoader();
        return instance;
    }

    void Initialize(std::string path_name, std::string file_name, std::string language);

    std::map<std::string, QString> GetString();
    QString GetString(std::string index);
    QStringList LoadLanuageList();
    QString GetLanguage();
private:
    void AddInvalidString(std::string str);

private:
    std::string m_file_name;
    std::map <std::string, QString> m_StringResource;
    QStringList  m_LanguageList;
    QString m_Language = "English";
};
}
static QString LoadString(std::string index)
{
//    using namespace ResourceLoader;
    return ResourceLoader::StringLoader::GetInstance()->GetString(index);
}

static QString GetLanguage()
{
    return ResourceLoader::StringLoader::GetInstance()->GetLanguage();
}

static QStringList LoadLangaugeList()
{
//    using namespace ResourceLoader;
    return ResourceLoader::StringLoader::GetInstance()->LoadLanuageList();
}

#endif // STRINGLOADER_H
