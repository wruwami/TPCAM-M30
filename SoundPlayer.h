#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QObject>
#include <QBuffer>
#include <QDataStream>

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
    QAudioOutput* audio = nullptr; // class member.
    QAudioDeviceInfo m_device;
    QAudioFormat format;
    QByteArray ba;
    QDataStream* s = nullptr;
protected slots:
    void handleStateChanged(QAudio::State);
signals:
    void audioStop();
};

#endif // SOUNDPLAYER_H
