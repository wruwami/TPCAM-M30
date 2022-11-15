#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QDir>
#include <QPixmap>

#define DEFAULT_PATH    "images"

static QPixmap LoadImage(std::string path_name, std::string file_name)
{
    QDir qdir;
    QString file_full_path;
#ifdef Q_OS_WIN
    file_full_path = qdir.absolutePath() + "\\" + DEFAULT_PATH + "\\" + QString::fromStdString(path_name) + "\\" + QString::fromStdString(file_name);
#else   /*Q_OS_LINUX*/
    file_full_path = qdir.absolutePath() + "/" + DEFAULT_PATH + "/" + QString::fromStdString(path_name) + "/" + QString::fromStdString(file_name);
#endif
    return QPixmap(file_full_path);
}

#endif // IMAGELOADER_H
