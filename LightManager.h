#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H


class LightManager
{
public:
    LightManager();
    void SwapLight();
private:
    bool isLightOn = true;
};

#endif // LIGHTMANAGER_H
