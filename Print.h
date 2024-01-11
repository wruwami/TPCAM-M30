/**
 * @file Print.h
 * @author wruwami (wruwami@naver.com)
 * @brief 일반프린터 출력 기능 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PRINT_H
#define PRINT_H

#include "FileFormat.h"

/**
 * @brief 일반프린터 출력 기능 클래스
 * 
 */
class Print
{
public:
    Print(AVFileFormat avFileFormat, QImage image);
};

#endif // PRINT_H
