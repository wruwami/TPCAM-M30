#include "SoundPlayer.h"

#include <QString>

#include <QAudioOutput>
#include <QFile>
#include <QSound>

#include <QtAVPlayer/qavaudiooutput.h>
#include <QVideoWidget>
#include <QtAVPlayer/qavaudioframe.h>

#include "FileManager.h"

#define DEFAULT_PATH    "audios"

SoundPlayer::SoundPlayer(QString file_name, QObject* parent) : QObject(parent)
{
    QString full_file_name = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + file_name;
    m_AVplayer.setSource(full_file_name);

    QObject::connect(&m_AVplayer, &QAVPlayer::audioFrame, [&](const QAVAudioFrame &frame) {
         // Access to the data
//         qDebug() << frame.format() << frame.data().size();
         m_output.play(frame);
    });
//    QAVAudioFrame frame;
//    QObject::connect(&m_AVplayer, &QAVPlayer::audioFrame, &m_AVplayer, [&](const QAVAudioFrame &f) { frame = f; });

//    QSound::play(full_file_name);

//    QFile sourceFile;   // class member.
//    QAudioOutput* audio; // class member.
//    {
//        sourceFile.setFileName(full_file_name);
//        sourceFile.open(QIODevice::ReadOnly);

//        QAudioFormat format;
//        // Set up the format, eg.
//        format.setSampleRate(8000);
//        format.setChannelCount(1);
//        format.setSampleSize(8);
//        format.setCodec("audio/pcm");
//        format.setByteOrder(QAudioFormat::LittleEndian);
//        format.setSampleType(QAudioFormat::UnSignedInt);

//        QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
//        if (!info.isFormatSupported(format)) {
////            qWarning() << "Raw audio format not supported by backend, cannot play audio.";
//            return;
//        }

//        audio = new QAudioOutput(format, this);
//        connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
//        audio->start(&sourceFile);
//    }
}

void SoundPlayer::play()
{
    m_AVplayer.play();
}
