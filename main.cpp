#include "MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QString>
#include "qdir.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkInterface>

#include "ConfigManager.h"
#include "StringLoader.h"
#include "DateFormatManager.h"
#include "thermal_printer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QFont font("NanumGothic");
    QApplication::setFont(font);

    QFile file(":/style/default.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());

    ConfigManager config = ConfigManager("parameter_setting3.json");
    QJsonObject json = config.GetConfig();
    SetDateFormat(json["date format items"].toArray()[json["date format selection"].toInt() - 1].toString());

    a.setStyleSheet(styleSheet);
    ConfigManager config2 = ConfigManager("parameter_setting6.json");
    json = config2.GetConfig();
    using namespace ResourceLoader;
    QJsonArray ja= json["language items"].toArray();
    int lang = json["language select"].toInt();
    StringLoader::GetInstance()->Initialize("strings", "stringTable.csv", ja[lang - 1].toString().toStdString());

    CreateWiFiReadThreadAndInitPrinter();

    MainWindow w;
//    w.show();
    w.setWindowFlags(Qt::Window);
    w.showFullScreen();

    return a.exec();
}
