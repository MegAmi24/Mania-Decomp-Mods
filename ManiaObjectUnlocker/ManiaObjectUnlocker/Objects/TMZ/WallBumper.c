#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "WallBumper.h"

ObjectWallBumper *WallBumper;

void WallBumper_StageLoad(void)
{
    if (CheckUnlock("WallBumper"))
        WallBumper->aniFrames = RSDK.LoadSpriteAnimation("TMZ1/WallBumper.bin", SCOPE_STAGE);

    Mod.Super(WallBumper->classID, SUPER_STAGELOAD, NULL);
}
