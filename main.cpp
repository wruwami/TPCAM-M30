#include "MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QString>
#include <Qdir>

#include "StringLoader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QFile file(":/style/default.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());

    a.setStyleSheet(styleSheet);

    QDir qdir;
    QString dir = qdir.absolutePath();
#ifdef Q_OS_WIN
    dir += "\\resource\\stringTable.csv";
#else   /*Q_OS_LINUX*/
    dir += "/resource/stringTable.csv";
#endif
    StringLoader::GetInstance()->Initialize(dir.toStdString(), "English");

    MainWindow w;
    w.show();

    return a.exec();
}
