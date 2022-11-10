#ifndef STRINGLOADER_H
#define STRINGLOADER_H


#include <map>
#include <QString>
#include <string>

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

    std::map<std::string, QString> LoadString();
    QString LoadString(std::string index);
private:
    void AddInvalidString(std::string str);
private:
    std::string m_file_name;
    std::map <std::string, QString> m_StringResource;
};

static QString LoadString(std::string index)
{
    return StringLoader::GetInstance()->LoadString(index);
}

#endif // STRINGLOADER_H
