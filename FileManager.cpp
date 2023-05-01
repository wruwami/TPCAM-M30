#include "FileManager.h"

#include "qdir.h"
#include <QDateTime>

#define DEFAULT_FILE_PATH   "files"

FileManager* FileManager::instance = nullptr;

QString FileManager::GetPath(QString name,Type type)
{
    if (type == eMMC)
        return GeteMMCPath() + "/" + DEFAULT_FILE_PATH + "/" + name;
    return GetSDPath() + "/" + DEFAULT_FILE_PATH + "/" + name;
}

QString FileManager::GetSubPath(QString name,Type type)
{
    QDateTime datetime = datetime.currentDateTime();
    QDir dir;
    if (type == eMMC)
        GeteMMCPath() + "/" + DEFAULT_FILE_PATH + "/" + name + "/" + datetime.toString("yyyyMMdd_HH");
    else
        GetSDPath() + "/" + DEFAULT_FILE_PATH + "/" + name + "/" + datetime.toString("yyyyMMdd_HH");
//    QDir dir(GetFirstPath() + "/" + DEFAULT_FILE_PATH + "/" + name + "/");
    if (!dir.exists())
    {
        if (type == eMMC)
            dir.mkdir(GeteMMCPath() + "/" + DEFAULT_FILE_PATH + "/" + name + "/" + datetime.toString("yyyyMMdd_HH"));
        else
            dir.mkdir(GetSDPath() + "/" + DEFAULT_FILE_PATH + "/" + name + "/" + datetime.toString("yyyyMMdd_HH"));
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

QString FileManager::GeteMMCPath()
{
    QDir dir;
    return dir.absolutePath();
}

QString FileManager::GetSDPath()
{
    QDir dir;
    return dir.absolutePath();
}
