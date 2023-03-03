#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <QString>
#include <QStringList>

struct AVFileFormat {
    char filePrefix[2]; //    1.      AV : Prefix for file (AV : Image + Video, AI : Only Image, VV : Only Video)
    char index[5];//    2.      00007 : Captured index during the day									파일 관리에서 인덱스
    char date[8];//    3.      20190109 : Date									날짜
    char time[7];//    4.      1644458 : 16(Hour), 44(Minute), 45(Second), 8 (1/10 Second)									시분초_1/10ms
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
    char unit;//    15.   S : Unit (S is Standard, B is British)									단위
    QString file_path;
};

static AVFileFormat GetFileFormat(QString file_path)
{
    int index = file_path.lastIndexOf('/');

    QString str = file_path.mid(index + 1, file_path.size() - index - 1);
    AVFileFormat avFileFormat;
    QStringList strList = str.split('_');
    sprintf(avFileFormat.filePrefix, strList[0].toStdString().c_str());
    sprintf(avFileFormat.index, strList[1].toStdString().c_str());
    sprintf(avFileFormat.date, strList[2].toStdString().c_str());
    sprintf(avFileFormat.time, strList[3].toStdString().c_str());
    avFileFormat.captureSpeed = strList[4];
    avFileFormat.speedLimit = strList[5];
    avFileFormat.captureSpeedLimit = strList[6];
    avFileFormat.distance = strList[7];
    avFileFormat.mode = strList[8];
    avFileFormat.latitude = strList[9];
    avFileFormat.longitude = strList[10];
    avFileFormat.location = strList[11];
    avFileFormat.userId = strList[12];
    avFileFormat.deviceId = strList[13].toStdString().c_str()[0];
    avFileFormat.file_path = file_path;
    return avFileFormat;
}

#endif // FILEFORMAT_H
