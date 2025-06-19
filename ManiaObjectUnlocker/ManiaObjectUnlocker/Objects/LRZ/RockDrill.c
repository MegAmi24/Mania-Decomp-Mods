#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "RockDrill.h"

ObjectRockDrill *RockDrill;

void RockDrill_StageLoad(void)
{
    if (CheckUnlock("RockDrill"))
        RockDrill->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/RockDrill.bin", SCOPE_STAGE);

    Mod.Super(RockDrill->classID, SUPER_STAGELOAD, NULL);
}
