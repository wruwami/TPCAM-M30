#include "SoundPlayer.h"

#include <QString>

#include <QAudioOutput>
#include <QFile>
#include <QSound>

#include <QtAVPlayer/qavaudiooutput.h>
#include <QVideoWidget>
#include <QtAVPlayer/qavaudioframe.h>
#include <QtAVPlayer/qaviodevice_p.h>

#include "FileManager.h"

#define DEFAULT_PATH    "audios"

SoundPlayer::SoundPlayer(QString file_name, QObject* parent) : QObject(parent)
{
    QString full_file_name = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + file_name;
//    m_AVplayer.setSource(full_file_name);

////    m_output = QAVAudioOutput(this);

//    QObject::connect(&m_AVplayer, &QAVPlayer::audioFrame, [&](const QAVAudioFrame &frame) {
//         // Access to the data
////         qDebug() << frame.format() << frame.data().size();
//         m_output.play(frame);
//    });
//    QAVAudioFrame frame;
//    QObject::connect(&m_AVplayer, &QAVPlayer::audioFrame, &m_AVplayer, [&](const QAVAudioFrame &f) { frame = f; });

//    QSound::play(full_file_name);

//    QFile sourceFile;   // class member.
    foreach (auto item, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
    {
        if (item.deviceName() == "default:CARD=rockchiprt5640c")
        {
            m_device = item;
            break;
        }
    }
//    m_device = QAudioDeviceInfo::defaultOutputDevice();
    audio = new QAudioOutput(m_device); // class member.
    {
        sourceFile.setFileName(full_file_name);
        sourceFile.open(QIODevice::ReadOnly);

        // Set up the format, eg.
        format.setSampleRate(8000);
        format.setChannelCount(1);
        format.setSampleSize(32);
        format.setCodec("audio/pcm");
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleType(QAudioFormat::SignedInt);

//        QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
        if (!m_device.isFormatSupported(format)) {
//            qWarning() << "Raw audio format not supported by backend, cannot play audio.";
            return;
        }

        audio = new QAudioOutput(format, this);
        connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
//        audio->start(&sourceFile);
    }
}

void SoundPlayer::play()
{
    audio->start(&sourceFile);
//    sourceFile.close();
//    m_AVplayer.play();
}
