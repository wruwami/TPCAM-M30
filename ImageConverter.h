/**
 * @file ImageConverter.h
 * @author wruwami (wruwami@naver.com)
 * @brief 열전사 프린터에서 이미지를 변환하는 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
