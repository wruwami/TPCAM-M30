#include "FileManager.h"

#include "qdir.h"

#define DEFAULT_FILE_PATH   "files"

FileManager* FileManager::instance = nullptr;

QString FileManager::GetPath(QString name)
{
    QDir dir;
    return dir.absolutePath() + "/" + DEFAULT_FILE_PATH + "/" + name;
}

bool FileManager::AddFile(QString name)
{

}
