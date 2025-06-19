#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "RockemSockem.h"

ObjectRockemSockem *RockemSockem;

void RockemSockem_StageLoad(void)
{
    Mod.Super(RockemSockem->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("RockemSockemSPZ1"))
        RockemSockem->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/RockemSockem.bin", SCOPE_STAGE);
}
