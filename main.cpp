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
    process.start("cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq");
    process.waitForFinished(-1);
    SetLogMsg(DEFAULT, "CPU0 clock : " + process.readAllStandardOutput());

    process.start("cat /sys/devices/system/cpu/cpu1/cpufreq/cpuinfo_cur_freq");
    process.waitForFinished(-1);
    SetLogMsg(DEFAULT, "CPU1 clock : " + process.readAllStandardOutput());

    process.start("cat /sys/devices/system/cpu/cpu2/cpufreq/cpuinfo_cur_freq");
    process.waitForFinished(-1);
    SetLogMsg(DEFAULT, "CPU2 clock : " + process.readAllStandardOutput());

    process.start("cat /sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_cur_freq");
    process.waitForFinished(-1);
    SetLogMsg(DEFAULT, "CPU3 clock : " + process.readAllStandardOutput());

    process.start("cat /sys/devices/system/cpu/cpu4/cpufreq/cpuinfo_cur_freq");
    process.waitForFinished(-1);
    SetLogMsg(DEFAULT, "CPU4 clock : " + process.readAllStandardOutput());

    process.start("cat /sys/devices/system/cpu/cpu5/cpufreq/cpuinfo_cur_freq");
    process.waitForFinished(-1);
    SetLogMsg(DEFAULT, "CPU5 clock : " + process.readAllStandardOutput());
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
    DateFormat dateformat;
    switch (json["date format selection"].toInt() - 1)
    {
    case 0:
    {
        dateformat = YYYYMMDD;
    }
        break;
    case 1:
    {
        dateformat = MMDDYYYY;
    }
        break;
    case 2:
    {
        dateformat = DDMMYYYY;
    }
        break;
    }

    SetDateFormat(dateformat);

    a.setStyleSheet(styleSheet);
    ConfigManager config2 = ConfigManager("parameter_setting6.json");
    json = config2.GetConfig();
    using namespace ResourceLoader;
    QJsonArray ja= json["start language items"].toArray();
    int lang = json["language select"].toInt();
    StringLoader::GetInstance()->Initialize("strings", "stringTable.csv", ja[lang - 1].toString().toStdString());

//    CreateWiFiReadThreadAndInitPrinter();

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


//    //generate key
//    QFile fileAES256Key(GETSDPATH(KEY) + "/comlaser-AES256-key.txt");
//    QFileInfo fileInfoAES256Key(fileAES256Key);
//    if(fileAES256Key.exists() && fileInfoAES256Key.size() >= 1000)
//    {
//        //file exists, do nothing
//        qDebug() << "key already exists";
//    }
//    else
//    {
//        //generate AES256 key
//        QString strCmd = "openssl rand -out "+GETSDPATH(KEY)+"/comlaser-AES256-key.txt"+" 32";
//        system(strCmd.toStdString().c_str());

//        //copy AES256 key to eMMc
//        strCmd = "sudo cp "+GETSDPATH(KEY)+"/comlaser-AES256-key.txt "+GeteMMCPath()+"/comlaser-AES256-key.txt";
//        system(strCmd.toStdString().c_str());

//        //generate RSA key pair
//        strCmd = "openssl genpkey -algorithm RSA -out "+GETSDPATH(KEY)+"/comlaser-secret-key.pem";
//        system(strCmd.toStdString().c_str());
//        strCmd = "openssl rsa -pubout -in "+GETSDPATH(KEY)+"/comlaser-secret-key.pem -out "+GETSDPATH(KEY)+"/comlaser-public-key.pem";
//        system(strCmd.toStdString().c_str());

//        //encrypt AES256 key using RSA key
//        strCmd = "openssl rsautl -encrypt -pubin -inkey "+GETSDPATH(KEY)+"/comlaser-public-key.pem"+" -in "
//                +GETSDPATH(KEY)+"/comlaser-AES256-key.txt"+" -out "+GETSDPATH(KEY)+"/comlaser-AES256-key.txt"+".en";
//        system(strCmd.toStdString().c_str());
//    }

    MainWindow w(a.send());
//    w.get(a.send());
//    w.show();
    w.setWindowFlags(Qt::Window);
    w.showFullScreen();

    return a.exec();
}
