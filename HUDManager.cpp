#include "HUDManager.h"

HUDManager::HUDManager()
{

}

// 0 Dot,
// 1 Cross,
// 2 Round,
// 3 Rectangle
void HUDManager::SetReticleShape(Shape shape)
{
    m_hud.writeNumberToFile("pointer_shape", shape);
}
