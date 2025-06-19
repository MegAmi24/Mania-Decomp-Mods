#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "CircleBumper.h"

ObjectCircleBumper *CircleBumper;

void CircleBumper_StageLoad(void)
{
    if (CheckUnlock("CircleBumperSPZ1"))
        CircleBumper->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/CircleBumper.bin", SCOPE_STAGE);

    Mod.Super(CircleBumper->classID, SUPER_STAGELOAD, NULL);
}
