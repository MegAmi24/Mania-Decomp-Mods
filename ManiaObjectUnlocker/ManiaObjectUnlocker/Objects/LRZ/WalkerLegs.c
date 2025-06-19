#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "WalkerLegs.h"

ObjectWalkerLegs *WalkerLegs;

void WalkerLegs_StageLoad(void)
{
    if (CheckUnlock("WalkerLegsLRZ1")) {
        WalkerLegs->aniFrames      = RSDK.LoadSpriteAnimation("LRZ1/WalkerLegs.bin", SCOPE_STAGE);
        WalkerLegs->particleFrames = RSDK.LoadSpriteAnimation("LRZ1/Particles.bin", SCOPE_STAGE);
    }

    Mod.Super(WalkerLegs->classID, SUPER_STAGELOAD, NULL);
}
