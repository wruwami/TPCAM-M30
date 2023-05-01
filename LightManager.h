#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H


class LightManager
{
public:
    LightManager();
    void SwapLight();
private:
    bool isLightOn = false;
};

#endif // LIGHTMANAGER_H
