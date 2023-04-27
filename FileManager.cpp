#include "FileManager.h"

#include "qdir.h"
#include <QDateTime>

#define DEFAULT_FILE_PATH   "files"

FileManager* FileManager::instance = nullptr;

QString FileManager::GetPath(QString name)
{

    return GetFirstPath() + "/" + DEFAULT_FILE_PATH + "/" + name;
}

QString FileManager::GetSubPath(QString name)
{
    QDateTime datetime = datetime.currentDateTime();
    QDir dir = GetFirstPath() + "/" + DEFAULT_FILE_PATH + "/" + name + "/" + datetime.toString("yyyyMMdd_HH");
//    QDir dir(GetFirstPath() + "/" + DEFAULT_FILE_PATH + "/" + name + "/");
    if (!dir.exists())
    {
        dir.mkdir(GetFirstPath() + "/" + DEFAULT_FILE_PATH + "/" + name + "/" + datetime.toString("yyyyMMdd_HH"));
    }
    return dir.absolutePath();
}


QString FileManager::AddFile(QString path_name, QString file_name)
{

}

QString FileManager::GetFile(QString name)
{
    QTime time = time.currentTime();
    if (name == "SC")
        return name + "_" + time.toString("mmss") + ".png";
    else
        return name + "_" + time.toString("mmss") + ".mkv";
}

QString FileManager::GetFirstPath()
{
    QDir dir;
    return dir.absolutePath();
}
