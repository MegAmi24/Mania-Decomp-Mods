#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "FrostThrower.h"

ObjectFrostThrower *FrostThrower;

void FrostThrower_StageLoad(void)
{
    if (CheckUnlock("FrostThrowerPSZ1"))
        FrostThrower->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/FrostThrower.bin", SCOPE_STAGE); // this doesn't actually exist in the final game...
    else if (CheckUnlock("FrostThrowerPSZ2"))
        FrostThrower->aniFrames = RSDK.LoadSpriteAnimation("PSZ2/FrostThrower.bin", SCOPE_STAGE);

    Mod.Super(FrostThrower->classID, SUPER_STAGELOAD, NULL);
}
