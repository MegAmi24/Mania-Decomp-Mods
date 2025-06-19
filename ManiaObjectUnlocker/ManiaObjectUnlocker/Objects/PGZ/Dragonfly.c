#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Dragonfly.h"

ObjectDragonfly *Dragonfly;

void Dragonfly_StageLoad(void)
{
    if (CheckUnlock("DragonflyPSZ1"))
        Dragonfly->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/Dragonfly.bin", SCOPE_STAGE);

    Mod.Super(Dragonfly->classID, SUPER_STAGELOAD, NULL);
}
