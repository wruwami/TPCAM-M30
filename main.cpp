#include "MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QString>
#include "qdir.h"

#include "StringLoader.h"
#include "SelfTestDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QFile file(":/style/default.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());

    a.setStyleSheet(styleSheet);

    StringLoader::GetInstance()->Initialize("strings", "stringTable.csv", "English");

    SelfTestDialog selfTestDialog;
    selfTestDialog.exec();

    MainWindow w;
//    w.show();
    w.showFullScreen();

    return a.exec();
}
