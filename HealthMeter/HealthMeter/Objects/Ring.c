#include "GameAPI/Game.h"
#include "Ring.h"

ObjectRing *Ring;

void Ring_Update(void)
{
    RSDK_THIS(Ring);

    if (self->state == Ring_State_Lost || self->state == Ring_State_LostFX || self->state == Ring_State_Big)
        destroyEntity(self);
    else
        Mod.Super(Ring->classID, SUPER_UPDATE, NULL);
}