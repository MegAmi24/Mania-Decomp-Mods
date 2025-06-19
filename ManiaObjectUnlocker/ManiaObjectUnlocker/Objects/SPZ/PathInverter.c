#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "PathInverter.h"

ObjectPathInverter *PathInverter;

void PathInverter_StageLoad(void)
{
    if (CheckUnlock("PathInverter"))
        PathInverter->aniFrames = RSDK.LoadSpriteAnimation("SPZ2/PathInverter.bin", SCOPE_STAGE);

    Mod.Super(PathInverter->classID, SUPER_STAGELOAD, NULL);
}
