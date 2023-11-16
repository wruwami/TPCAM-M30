#ifndef VERSION_H
#define VERSION_H

#endif // VERSION_H


#define SW_VER          "v0.0.0.12 "
//#define	SW_BUILDDATE	__DATE__
//#define	SW_BUILDTIME	__TIME__

/*********************************************************************************************************
 DATE(YYYY.MM.DD)   TIME(hh:mm) VERSION(vX.X.X.X)
    1. Update1(Update details, Bug fixes ...)
    2. Update2(Update details, Bug fixes ...)
    3.    .
    4.    .
    5.    .
*********************************************************************************************************/

/*
========================================================================================================
--------------------------------------------------------------------------------------------------------
2023.11.14  21:00   v0.0.0.12 - KMS
    1. modify styleSheet
    2. modify label state(enable, disable) in setting
    3. change way of searching wifi in wifiSearchWidget.cpp
    4. change codec in ffmpeg command

--------------------------------------------------------------------------------------------------------
2023.11.14  16:00   v0.0.0.11 - LJH
    1. modify ui
         - Clear table and filename when loading saved image from file manager
    2. modify password widget focusing
    3. modify video saving resolution from auto mode

--------------------------------------------------------------------------------------------------------
2023.11.13  14:00   v0.0.0.9 - KMS
    1. modify json
    2. modify ui
    3. bug fix(NightMode)

--------------------------------------------------------------------------------------------------------
2023.11.13  14:00   v0.0.0.9 - KMS
    1. bug fix(NightMode, GPS, Camera-Exposure, F+,F-)

--------------------------------------------------------------------------------------------------------
2023.11.13  01:00   v0.0.0.8 - LJH
    1. modify EnfocementComponentWidget ui(capture speed, button font size)
    2. flash bug fix(set the light to turn on only at night)
    3. modify still shot image info(Not displayed if GPS is not connected)

--------------------------------------------------------------------------------------------------------
2023.11.11  17:00   v0.0.0.7 - KMS
    1. modify ui
    2. add font
    3. bug fix(setting-language)
    4. change button borderLine width -> 2px

--------------------------------------------------------------------------------------------------------
2023.11.07  15:00   v0.0.0.6 - LJH
    1. add system log(CPU 0~5 clock)

--------------------------------------------------------------------------------------------------------
2023.11.07  09:00   v0.0.0.5 - KMS
    1. modify ui
    2. add font
    3. apply multi-language to setting's combobox
    4. lock video file when it is being created

--------------------------------------------------------------------------------------------------------
2023.11.03  16:00   v0.0.0.4 - LJH
    1. add system log case(DEFAULT).
    2. mod combobox UI(CustomComboBox.h)
    3. mod widget position & ratio(IndicatorCameraExposeWidget.ui, IndicatorCameraFocusWidget.ui)
    4. CPU clock to system log when program starts.(main.cpp)

--------------------------------------------------------------------------------------------------------
2023.11.01  11:30   v0.0.0.3 - LJH
    1. modified the logic for saving images in v4l2.
    2. gstreamer shared memory start : main.cpp

--------------------------------------------------------------------------------------------------------
2023.10.31  17:00   v0.0.0.2 - LJH
    1. gstreamer shared memory logic modification.
    2. modified sd card capacity display : available capacity -> used capacity

--------------------------------------------------------------------------------------------------------
2023.10.27  09:20   v0.0.0.1 - LJH
    1. Start versioning.
    2. Right align version string on login page.

========================================================================================================
*/
