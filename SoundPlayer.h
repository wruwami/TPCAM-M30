#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QObject>
#include <QBuffer>
#include <QDataStream>
#include <QMap>

#include <QtAVPlayer/qavplayer.h>
#include <QtAVPlayer/qavaudiooutput.h>
#include <QFile>
#include <QAudioOutput>

enum PlayType {
    Click,
    Booting,
    ReBooting,
    Snapshot,
    SelfTestFailed,
};

/**
 * @brief 사운드 플레이 기능 클래스
 * 
 */
class SoundPlayer : public QObject
{
    Q_OBJECT
private:
    explicit SoundPlayer(QObject *parent = 0);
    SoundPlayer(const SoundPlayer& other);
    virtual ~SoundPlayer();
    static SoundPlayer* instance;
public:
    static SoundPlayer* GetInstance()
    {
        if(instance == nullptr) instance = new SoundPlayer();
        return instance;
    }
    void play(PlayType);
private:
//    QAVPlayer m_AVplayer;
//    QAVAudioOutput m_output = QAVAudioOutput(this);
    QAudioOutput* audio = nullptr; // class member.
    QAudioDeviceInfo m_device;
    QAudioFormat format;

    QMap<PlayType, QDataStream*> sMap;
protected slots:
    void handleStateChanged(QAudio::State);
signals:
    void audioStop();
};

#endif // SOUNDPLAYER_H
