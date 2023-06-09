#include "LcdBrightManager.h"
#include "ConfigManager.h"
#include <unistd.h>


LcdBrightManager::LcdBrightManager()
{

    ConfigManager config = ConfigManager("parameter_setting3.json");
    QJsonObject object = config.GetConfig();
    int bright = object["lcd brightness selection"].toInt();

//    system("echo 1 > /sys/class/backlight/backlight/bl_power");
//    sleep(1);
//    system("echo 0 > /sys/class/backlight/backlight/bl_power");
//    sleep(1);

    switch (bright)
    {
    case 1:
    {
        system("echo 20 > /sys/class/backlight/backlight/brightness");
    }
        break;
    case 2:
    {
        system("echo 128 > /sys/class/backlight/backlight/brightness");
    }
        break;
    case 3:
    {
        system("echo 255 > /sys/class/backlight/backlight/brightness");
    }
        break;

    }
}
