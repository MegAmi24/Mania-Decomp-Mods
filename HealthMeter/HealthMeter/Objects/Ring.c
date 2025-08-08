#include "GameAPI/Game.h"
#include "Ring.h"

StateMachine(Ring_State_Lost) = NULL;
StateMachine(Ring_State_LostFX) = NULL;
StateMachine(Ring_State_Big) = NULL;

ObjectRing *Ring;

void Ring_LateUpdate(void)
{
    RSDK_THIS(Ring);

    if (self->state == Ring_State_Lost || self->state == Ring_State_LostFX || self->state == Ring_State_Big)
        destroyEntity(self);
    else
        Mod.Super(Ring->classID, SUPER_LATEUPDATE, NULL);
}
