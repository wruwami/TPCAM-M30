#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>

class FileManager
{
private:
    FileManager() {}
    FileManager(const FileManager& other);
    ~FileManager() {}
    static FileManager* instance;
public:
    static FileManager* GetInstance()
    {
        if(instance == nullptr) instance = new FileManager();
        return instance;
    }
    QString GetPath(QString name);
    QString GetSubPath(QString name);
    QString AddFile(QString path_name, QString file_name);
private:
    QString GetFirstPath();

};

static QString GetPath(QString name)
{
    return FileManager::GetInstance()->GetPath(name);
}
static QString AddFile(QString path_name, QString file_name)
{
    return FileManager::GetInstance()->AddFile(path_name, file_name);
}
static QString GetSubPath(QString name)
{
    return FileManager::GetInstance()->GetSubPath("name");
}

#endif // FILEMANAGER_H
