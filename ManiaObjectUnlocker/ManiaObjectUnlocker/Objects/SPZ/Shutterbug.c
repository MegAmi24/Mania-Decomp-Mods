#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Shutterbug.h"

ObjectShutterbug *Shutterbug;

void Shutterbug_StageLoad(void)
{
    Mod.Super(Shutterbug->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("ShutterbugSPZ1"))
        Shutterbug->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/Shutterbug.bin", SCOPE_STAGE);
}
