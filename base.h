/**
 * @file base.h
 * @author wruwami (wruwami@naver.com)
 * @brief 공통 사용되는 기본 파라미터
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef BASE_H
#define BASE_H

namespace TPCAM_M30 {
enum DefaultHUDValue {
    HUD_x = 6,
    HUD_y = 6,
};

enum DefaultLaserValue {
    Laser_x = 960,
    Laser_y = 540,
};

enum LaserArea {
    x1 = 660,
    x2 = 1260,
    y1 = 390,
    y2 = 690
};

}


#endif // BASE_H
