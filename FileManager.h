#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>

enum Type
{
    eMMC,
    SD
};

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
    QString GetPath(QString name,Type type);
    QString GetSubPath(QString name,Type type);
    QString AddFile(QString path_name, QString file_name);
    QString GetFile(QString name);
    QString GeteMMCPath();
    QString GetSDPath();
    QString GetUSBPath();
};

static QString GetPath(QString name, Type type)
{
    return FileManager::GetInstance()->GetPath(name, type);
}
static QString AddFile(QString path_name, QString file_name)
{
    return FileManager::GetInstance()->AddFile(path_name, file_name);
}
static QString GetSubPath(QString name, Type type)
{
    return FileManager::GetInstance()->GetSubPath(name, type);
}
static QString GetFile(QString name)
{
    return FileManager::GetInstance()->GetFile(name);
}
static QString GeteMMCPath()
{
    return FileManager::GetInstance()->GeteMMCPath();
}

static QString GetSDPath()
{
    return FileManager::GetInstance()->GetSDPath();
}

static QString GetUSBPath()
{
    return FileManager::GetInstance()->GetUSBPath();
}

#endif // FILEMANAGER_H
