#ifndef MEDIAOBJECT_H
#define MEDIAOBJECT_H



#include "mediaservice.h"

class MediaObject : public QMediaObject
{
public:
    explicit MediaObject(VideoRenderer *vr, QObject* parent = nullptr)
        : QMediaObject(parent, new MediaService(vr, parent))
    {
    }
};
#endif // MEDIAOBJECT_H
