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
    bool AddFile(QString name);

};

static QString GetPath(QString name)
{
    return FileManager::GetInstance()->GetPath(name);
}

#endif // FILEMANAGER_H
