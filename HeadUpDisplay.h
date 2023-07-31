#ifndef CHEADUPDISPLAY_H
#define CHEADUPDISPLAY_H

#include <QObject>
#include <QTimer>

class CHeadUpDisplay : public QObject
{
    Q_OBJECT
public:
    CHeadUpDisplay();
    void initDisplay();
    bool writeNumberToFile(QString fileName, int value);
    int readNumberFromFile(QString fileName);

public slots:
    void showDistanceSensitivity(float fDistance, int nSensitivity);
    void showSpeedDistanceSensitivity(float fSpeed, float distance);
    void showCaptureSpeedDistance(float fSpeed, float distance, int);
    void hideSpeed();
    void hideDistance();

public:
    //Speed
    QTimer m_SpeedTimer;
    QTimer m_DistanceTimer;
    float m_fPastSpeed = 0;
    bool m_bIsSpeedDispOn = false;

    //cnrk
    bool m_bSensitivityOn = true;
    int m_nREC = 1; //1 - REC 미표시, 2 - REC 표시
    int m_nDistanceUnit = 2;

    void changeToSpeedCheckMode();
    void changeToAlineMode();


};

#endif // CHEADUPDISPLAY_H
