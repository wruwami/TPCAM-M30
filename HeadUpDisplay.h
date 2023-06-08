#ifndef CHEADUPDISPLAY_H
#define CHEADUPDISPLAY_H

#include <QString>
#include <QElapsedTimer>

class CHeadUpDisplay
{
public:
    CHeadUpDisplay();
    void initDisplay();
    bool writeNumberToFile(QString fileName, int value);
    int readNumberFromFile(QString fileName);
    void showSpeedDistance(int speed, float distance);
    void showSpeedDistanceSensitivity(int speed, float distance, int sensitivity);



    //Speed
    QElapsedTimer m_SpeedTimer;
    int m_fPastSpeed = 0;

    //cnrk
    bool m_bSensitivityOn = true;
    int m_nDistanceUnit = 2;
};

#endif // CHEADUPDISPLAY_H
