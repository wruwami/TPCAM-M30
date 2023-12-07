#include "SoundPlayer.h"

#include <QString>

#include <QtAVPlayer/qavaudiooutput.h>
#include <QVideoWidget>

#include "FileManager.h"

#define DEFAULT_PATH    "audios"

SoundPlayer::SoundPlayer(QString file_name)
{
    QString full_file_name = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + file_name;
    m_AVplayer.setSource(full_file_name);
}

void SoundPlayer::play()
{
    m_AVplayer.play();
}
