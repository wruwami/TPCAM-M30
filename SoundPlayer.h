#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QObject>

#include <QtAVPlayer/qavplayer.h>
#include <QtAVPlayer/qavaudiooutput.h>
#include <QFile>
#include <QAudioOutput>


class SoundPlayer : public QObject
{
    Q_OBJECT
public:
    explicit SoundPlayer(QString, QObject *parent = 0);
    void play();
private:
//    QAVPlayer m_AVplayer;
//    QAVAudioOutput m_output = QAVAudioOutput(this);
    QFile sourceFile;   // class member.
    QAudioOutput* audio; // class member.
    QAudioDeviceInfo m_device;
    QAudioFormat format;
};

#endif // SOUNDPLAYER_H
