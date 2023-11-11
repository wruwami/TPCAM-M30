#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <QString>
#include <QStringList>
#include <QFileInfo>

struct AVFileFormat {
    char filePrefix[2 + 1]; //    1.      AV : Prefix for file (AV : Image + Video, AI : Only Image, VV : Only Video)
    char index[5 + 1];//    2.      00007 : Captured index during the day									파일 관리에서 인덱스
    char date[8 + 1];//    3.      20190109 : Date									날짜
    char time[7 + 1];//    4.      1644458 : 16(Hour), 44(Minute), 45(Second), 8 (1/10 Second)									시분초_1/10ms
    QString captureSpeed;//    5.      +0200 : Captured Speed (measured by laser)									단속 속도
    QString speedLimit;//    6.      0100 : Speed Limit									제한 속도
    QString captureSpeedLimit;//    7.      0100 : Capture Speed Limit									갭쳐 속도
    QString distance;//    8.      0062 : Distance between H20 and car									단속 거리
    QString mode;//    9.      UAN01 : User mode, Image + Video mode, Normal car, Zoom index (Currently 60m)									모드들의 조합 표시
    QString latitude;//    10.   +00.000000 : Latitude									위도
    QString longitude;//    11.   +000.00000 : Longitude									경도
    QString location;//    12.   SEOUL : Location input by user									Location
    QString userId;//    13.   Mike : User ID									유저 ID
    QString deviceId;//    14.   TP00001 : Device ID									디바이스 ID
    char unit[1 + 1];//    15.   S : Unit (S is Standard, B is British)									단위
    QString file_path;
};

//struct ScreenFileFormat {
//    char source[2]; // SC:image SR:video
//    QString file_path;
//    char date[8];//    3.      20190109 : Date									날짜
//    char time[6];//    4.      1644458 : 16(Hour), 44(Minute), 45(Second),
//};

static AVFileFormat GetFileFormat(QString file_path)
{
    int index = file_path.lastIndexOf('/');
    int index2 = file_path.lastIndexOf('.');

    QString file_base_name = file_path.mid(index + 1, file_path.size() - index - file_path.size() + index2 - 1);
//    QString file_base_name = QFileInfo(file_path).baseName();

    AVFileFormat avFileFormat;
    QStringList strList = file_base_name.split('_');
    memcpy(avFileFormat.filePrefix, strList[0].toStdString().c_str(), strList[0].size());
    avFileFormat.filePrefix[2] = '\0';
    if (!strcmp(avFileFormat.filePrefix, "SC") || !strcmp(avFileFormat.filePrefix, "SR"))
    {
        memcpy(avFileFormat.date, strList[1].toStdString().c_str(), strList[1].size());
        avFileFormat.date[8] = '\0';
        memcpy(avFileFormat.time, strList[2].toStdString().c_str(), strList[2].size());
        avFileFormat.time[6] = '\0';
        avFileFormat.time[7] = '\0';
        memset(avFileFormat.index, 0, 5);
        memset(avFileFormat.unit, 0, 2);

        avFileFormat.file_path = file_path;
    }
    else
    {
        memcpy(avFileFormat.index, strList[1].toStdString().c_str(), strList[1].size());
        avFileFormat.index[5] = '\0';
        memcpy(avFileFormat.date, strList[2].toStdString().c_str(), strList[2].size());
        avFileFormat.date[8] = '\0';
        memcpy(avFileFormat.time, strList[3].toStdString().c_str(), strList[3].size());
        avFileFormat.time[7] = '\0';
        avFileFormat.captureSpeed = strList[4];
        avFileFormat.speedLimit = strList[5];
        avFileFormat.captureSpeedLimit = strList[6];
        avFileFormat.distance = strList[7];
        avFileFormat.mode = strList[8];
        avFileFormat.latitude = strList[9];
        avFileFormat.longitude = strList[10];
        avFileFormat.location = strList[11];
        avFileFormat.userId = strList[12];
        if (strList.size() == 15)
        {
            avFileFormat.deviceId = strList[13];
        }
        else if (strList.size() == 16)
        {
            avFileFormat.deviceId = strList[13] + "_" + strList[14];
        }
        else if (strList.size() == 17)
        {
            avFileFormat.deviceId = strList[13] + "_" + strList[14] + "_" + strList[15];
        }


        avFileFormat.file_path = file_path;
        strcpy(avFileFormat.unit, "S");
//         = 'S';

    }
    return avFileFormat;
}

//static ScreenFileFormat GetScreenFileFormat(QString file_path)
//{
//    int index = file_path.lastIndexOf('/');

//    QString str = file_path.mid(index + 1, file_path.size() - index - 1);
//    QStringList strList = str.split('_');

//    ScreenFileFormat screenFileFormat;
//    memcpy(screenFileFormat.source, strList[0].toStdString().c_str(), strList[0].size());
//    memcpy(screenFileFormat.date, strList[1].toStdString().c_str(), strList[1].size());
//    memcpy(screenFileFormat.source, strList[2].toStdString().c_str(), strList[2].size());
//    screenFileFormat.file_path = file_path;
//    return screenFileFormat;
//}

#endif // FILEFORMAT_H
