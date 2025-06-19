#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "DiveEggman.h"

ObjectDiveEggman *DiveEggman;

void DiveEggman_StageLoad(void)
{
    if (CheckUnlock("DiveEggman")) {
        DiveEggman->diveFrames = RSDK.LoadSpriteAnimation("HCZ/DiveEggman.bin", SCOPE_STAGE);
        DiveEggman->aniFrames  = RSDK.LoadSpriteAnimation("Eggman/EggmanHCZ1.bin", SCOPE_STAGE);
    }

    Mod.Super(DiveEggman->classID, SUPER_STAGELOAD, NULL);
}
