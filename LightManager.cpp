#include "LightManager.h"

#include <stdlib.h>

LightManager::LightManager()
{
    system("echo 154 | true || sudo tee -a /sys/class/gpio/export > /dev/null");
    system("echo 154 > /sys/class/gpio/export");
    system("echo out | sudo tee -a /sys/class/gpio/gpio154/direction > /dev/null");

}

void LightManager::SwapLight()
{
    system("echo 1 > /sys/class/gpio/gpio154/value");
    system("echo 0 > /sys/class/gpio/gpio154/value");
}
