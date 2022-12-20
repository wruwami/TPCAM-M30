#include "MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QString>
#include "qdir.h"

#include "StringLoader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QFont font("NanumGothic");
    QApplication::setFont(font);

    QFile file(":/style/default.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());

    a.setStyleSheet(styleSheet);
    using namespace ResourceLoader;
    StringLoader::GetInstance()->Initialize("strings", "stringTable.csv", "English");

    MainWindow w;
//    w.show();
    w.setWindowFlags(Qt::Window);
    w.showFullScreen();

    return a.exec();
}
