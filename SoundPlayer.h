#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QtAVPlayer/qavplayer.h>

class SoundPlayer
{
public:
    SoundPlayer(QString);
    void play();
private:
    QAVPlayer m_AVplayer;
};

#endif // SOUNDPLAYER_H
