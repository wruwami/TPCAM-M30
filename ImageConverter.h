#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QImage>

class ImageConverter
{
public:
    ImageConverter(QImage image);
    void Convert();
private:
    QImage m_image;
};

#endif // IMAGECONVERTER_H
