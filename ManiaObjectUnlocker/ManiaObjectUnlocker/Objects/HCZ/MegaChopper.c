#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "MegaChopper.h"

ObjectMegaChopper *MegaChopper;

void MegaChopper_StageLoad(void)
{
    if (CheckUnlock("MegaChopper"))
        MegaChopper->aniFrames = RSDK.LoadSpriteAnimation("HCZ/MegaChopper.bin", SCOPE_STAGE);

    Mod.Super(MegaChopper->classID, SUPER_STAGELOAD, NULL);
}
