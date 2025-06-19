#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "LavaGeyser.h"

ObjectLavaGeyser *LavaGeyser;

void LavaGeyser_StageLoad(void)
{
    if (CheckUnlock("LavaGeyserLRZ1"))
        LavaGeyser->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/LavaGeyser.bin", SCOPE_STAGE);

    Mod.Super(LavaGeyser->classID, SUPER_STAGELOAD, NULL);
}
