#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Iwamodoki.h"

ObjectIwamodoki *Iwamodoki;

void Iwamodoki_StageLoad(void)
{
    if (CheckUnlock("IwamodokiLRZ1"))
        Iwamodoki->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/Iwamodoki.bin", SCOPE_STAGE);

    Mod.Super(Iwamodoki->classID, SUPER_STAGELOAD, NULL);
}
