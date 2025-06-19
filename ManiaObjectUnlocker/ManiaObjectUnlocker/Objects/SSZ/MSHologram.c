#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "MSHologram.h"

ObjectMSHologram *MSHologram;

void MSHologram_StageLoad(void)
{
    if (CheckUnlock("MSHologramSSZ1"))
        MSHologram->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/MSHologram.bin", SCOPE_STAGE);

    Mod.Super(MSHologram->classID, SUPER_STAGELOAD, NULL);
}
