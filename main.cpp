#include "MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QString>
#include "qdir.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkInterface>
#include <QProcess>

#include "ConfigManager.h"
#include "StringLoader.h"
#include "DateFormatManager.h"
#include "thermal_printer.h"
#include "StorageManager.h"
#include "Application.h"
#include "Logger.h"
#include "FileManager.h"
#include "version.h"
#include "GstShmMgr.h"
#include "WidgetSize.h"

QString g_AppVersion = QString(SW_VER);

void CheckCpuClock()
{
    QProcess process;
    //process.start("cpufreq-info | grep current");
    process.start("cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq");
    process.waitForFinished(-1);

    SetLogMsg(DEFAULT, "CPU clock : " + process.readAllStandardOutput());
    SetLogMsg(DEFAULT, "CPU clock err : " + process.readAllStandardError());
}

int main(int argc, char *argv[])
{
    CheckCpuClock();
    GstShmMgr::getInstance();

    Application a(argc, argv);
    Application::setAttribute(Qt::AA_EnableHighDpiScaling);

    QFont font("NanumGothic");
    font.setPixelSize(GetFontSize(23));
    Application::setFont(font);

    SetLogMsg(POWER_ON);

    QFile file(":/style/default.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    file.close();

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

//    system("sudo timedatectl set-ntp 0");
//    system("sudo /home/firefly/start.sh");
    QString cmd = "sudo chmod +x "+GeteMMCPath()+"/"+"start.sh";
    system(cmd.toStdString().c_str());
    cmd = "sudo chmod +x "+GeteMMCPath()+"/"+"command_change.sh";
    system(cmd.toStdString().c_str());
    cmd = "sudo chmod +x "+GeteMMCPath()+"/"+"command_origin.sh";
    system(cmd.toStdString().c_str());
    cmd = "sudo "+GeteMMCPath()+"/"+"start.sh";
    system(cmd.toStdString().c_str());


    MainWindow w(a.send());
//    w.get(a.send());
//    w.show();
    w.setWindowFlags(Qt::Window);
    w.showFullScreen();

    return a.exec();
}
