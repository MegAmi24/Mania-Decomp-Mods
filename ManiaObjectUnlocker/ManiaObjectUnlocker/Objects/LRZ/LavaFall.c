#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "LavaFall.h"

ObjectLavaFall *LavaFall;

void LavaFall_StageLoad(void)
{
    if (CheckUnlock("LavaFall"))
        LavaFall->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/LavaFall.bin", SCOPE_STAGE);

    Mod.Super(LavaFall->classID, SUPER_STAGELOAD, NULL);
}
