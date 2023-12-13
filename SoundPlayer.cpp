#include "SoundPlayer.h"

#include "unistd.h"

#include <QString>

#include <QAudioOutput>
#include <QFile>
#include <QSound>
#include <QDebug>

#include <QtAVPlayer/qavaudiooutput.h>
#include <QVideoWidget>
#include <QtAVPlayer/qavaudioframe.h>
#include <QtAVPlayer/qaviodevice_p.h>

#include "FileManager.h"

#define DEFAULT_PATH    "audios"

SoundPlayer::SoundPlayer(QString file_name, QObject* parent) : QObject(parent)
{
    QString full_file_name = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + file_name;

    sourceFile.setFileName(full_file_name);
    sourceFile.open(QIODevice::ReadOnly);
    ba = sourceFile.readAll();
    s = new QDataStream(ba);
    sourceFile.close();
//    sourceFile.close();
    m_buffer = new QBuffer;
    m_buffer->open(QIODevice::ReadWrite);
    m_buffer->seek(0);
    m_buffer->setData(ba);
    qDebug() << m_buffer->buffer();
    m_buffer->close();
    qDebug() << m_buffer->buffer();
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

//    QFile sourceFile;   // class member.
//    foreach (auto item, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
//    {
//        if (item.deviceName() == "default:CARD=rockchiprt5640c")
//        {
//            m_device = item;
//            break;
//        }
//    }
    m_device = QAudioDeviceInfo::defaultOutputDevice();
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
//        audio->setBufferSize(32768);
//        if (audio->error() != QAudio::NoError) {
//            qDebug() << "Problem playing sound";
//        }
//        audio->setNotifyInterval(1);
        connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));

    }
}

void SoundPlayer::play()
{
//    m_buffer->close();
//    m_buffer->open(QIODevice::ReadOnly | QIODevice::Unbuffered);
//    QDataStream s(m_buffer);
//    if (m_buffer->device()->isReadable())
//    m_buffer->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
//    if (s)
//    {
//        delete s;
//        s = nullptr;
//    }
//    s = new QDataStream(ba);
//    qDebug() << s->device().;
//    s->device()->seek(0);
//    qDebug() << s->device()->pos();
//    audio->start(s->device());
//    QDataStream st = QDataStream(ba);

//    if(sourceFile.isOpen()==false)
//    {
//        audio->stop();
//        sourceFile.close();
//        qDebug() << sourceFile.open(QIODevice::ReadOnly);
//        audio->start(&sourceFile);
//    }
    qDebug() << audio->bufferSize();
    s->device()->seek(0);
    audio->start(s->device());

//    if (!m_buffer->isOpen())
//        m_buffer->open(QIODevice::ReadOnly);
//    m_buffer->seek(0);
//    qDebug() << m_buffer->buffer();
//    audio->start(m_buffer);

    //    sleep(10);
//    m_buffer->close();
//    m_buffer->close();
//    sourceFile.close();
        //    m_AVplayer.play();
}

void SoundPlayer::handleStateChanged(QAudio::State state)
{
    switch (state) {
        case QAudio::IdleState:
            // Finished playing (no more data)
            audio->stop();
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
