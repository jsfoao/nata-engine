#include "core.h"

namespace Nata
{
    void Destroy(NWorld* world, EEntity* entity)
    {
        world->Destroy(entity);
    }
}