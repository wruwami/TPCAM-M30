#include "SoundPlayer.h"

#include "unistd.h"

#include <QString>
#include <QEventLoop>

#include <QAudioOutput>
#include <QFile>
#include <QSound>
#include <QDebug>
#include <QList>

#include <QtAVPlayer/qavaudiooutput.h>
#include <QVideoWidget>
#include <QtAVPlayer/qavaudioframe.h>
#include <QtAVPlayer/qaviodevice_p.h>

#include "FileManager.h"

#define DEFAULT_PATH    "audios"

QMap<PlayType, QString> soundPlayMap;// = {<Booting, "byebye.raw">, "reboot_system.raw", "no_memory_card.raw", "snapshot.raw", "button.raw"};

SoundPlayer* SoundPlayer::instance = nullptr;

SoundPlayer::SoundPlayer(QObject* parent) : QObject(parent)
{
//    QString full_file_name = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + file_name;

    soundPlayMap[Booting] = "byebye.raw";
    soundPlayMap[ReBooting] = "reboot_system.raw";
    soundPlayMap[Snapshot] = "snapshot.raw";
    soundPlayMap[Click] = "button.raw";
    soundPlayMap[SelfTestFailed] = "no_memory_card.raw";

//    foreach (auto item, soundPlayMap)
    QMapIterator<PlayType, QString> it(soundPlayMap);
    while(it.hasNext())
    {
        auto item = it.next();
//        item.key()
        QString full_file_name = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + item.value();

        QFile sourceFile;
        sourceFile.setFileName(full_file_name);
        sourceFile.open(QIODevice::ReadOnly);
        QByteArray ba = sourceFile.readAll();
        QDataStream* s = new QDataStream(ba);
        sMap[item.key()] = s;
        sourceFile.close();
    }
//    QFile sourceFile;
//    sourceFile.setFileName(full_file_name);
//    sourceFile.open(QIODevice::ReadOnly);
//    ba = sourceFile.readAll();
////    s = new QDataStream(ba);
//    sourceFile.close();
//    sourceFile.close();
//    m_buffer = new QBuffer;
//    m_buffer->open(QIODevice::ReadWrite);
//    m_buffer->seek(0);
//    m_buffer->setData(ba);
//    qDebug() << m_buffer->buffer();
//    m_buffer->close();
//    qDebug() << m_buffer->buffer();
//    m_buffer->close();
    //    m_buffer.setData(sourceFile.readAll());
//    m_buffer.close();


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

    foreach (auto item, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
    {
        if (item.deviceName() == "default:CARD=rockchiprt5640c")
        {
            m_device = item;
            break;
        }
    }
//    m_device = QAudioDeviceInfo::defaultOutputDevice();
//    audio = new QAudioOutput(m_device); // class member.
    {

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

        audio = new QAudioOutput(m_device, format);
        if (audio->error() != QAudio::NoError) {
            qDebug() << "Problem playing sound";
        }
//        audio->setNotifyInterval(1);
        connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));

    }
}

SoundPlayer::~SoundPlayer()
{
    delete audio;
    QMapIterator<PlayType, QDataStream *> it(sMap);
    while(it.hasNext())
    {
        auto item = it.next();
        delete item.value();
    }
///    delete sMap;
}

void SoundPlayer::play(PlayType type)
{
    if (!audio)
        return;
//    if (audio->state() != QAudio::ActiveState)
//        return;

    audio->reset();
    sMap[type]->device()->seek(0);
    audio->start(sMap[type]->device());
}

void SoundPlayer::handleStateChanged(QAudio::State state)
{
    switch (state) {
        case QAudio::IdleState:
            // Finished playing (no more data)
            audio->stop();
            emit audioStop();
//            sourceFile.close();
//            delete audio;
            break;

        case QAudio::StoppedState:
            // Stopped for other reasons
            if (audio->error() != QAudio::NoError) {
                qDebug() << audio->error();
//               s->device()->open(QIODevice::ReadOnly);
//                audio->reset();
            }
            else
            {
                audio->stop();
            }

            break;

        default:
            // ... other cases as appropriate
            break;
    }
}
