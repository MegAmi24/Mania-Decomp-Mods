#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "HangPoint.h"

ObjectHangPoint *HangPoint;

void HangPoint_StageLoad(void)
{
    if (CheckUnlock("HangPoint"))
        HangPoint->aniFrames = RSDK.LoadSpriteAnimation("FBZ/HangPoint.bin", SCOPE_STAGE);

    Mod.Super(HangPoint->classID, SUPER_STAGELOAD, NULL);
}
