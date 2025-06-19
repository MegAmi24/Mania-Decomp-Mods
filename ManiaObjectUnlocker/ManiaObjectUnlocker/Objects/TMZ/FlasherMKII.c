#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "FlasherMKII.h"

ObjectFlasherMKII *FlasherMKII;

void FlasherMKII_StageLoad(void)
{
    if (CheckUnlock("FlasherMKII"))
        FlasherMKII->aniFrames = RSDK.LoadSpriteAnimation("TMZ1/FlasherMKII.bin", SCOPE_STAGE);

    Mod.Super(FlasherMKII->classID, SUPER_STAGELOAD, NULL);
}
