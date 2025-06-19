#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "MSOrb.h"

ObjectMSOrb *MSOrb;

void MSOrb_StageLoad(void)
{
    if (CheckUnlock("MSOrb"))
        MSOrb->aniFrames = RSDK.LoadSpriteAnimation("SSZ2/MetalSonic.bin", SCOPE_STAGE);

    Mod.Super(MSOrb->classID, SUPER_STAGELOAD, NULL);
}
