#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "RollerMKII.h"

ObjectRollerMKII *RollerMKII;

void RollerMKII_StageLoad(void)
{
    if (CheckUnlock("RollerMKII"))
        RollerMKII->aniFrames = RSDK.LoadSpriteAnimation("MSZ/RollerMKII.bin", SCOPE_STAGE);

    Mod.Super(RollerMKII->classID, SUPER_STAGELOAD, NULL);
}
