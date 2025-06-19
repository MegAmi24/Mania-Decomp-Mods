#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "YoyoPulley.h"

ObjectYoyoPulley *YoyoPulley;

void YoyoPulley_StageLoad(void)
{
    if (CheckUnlock("YoyoPulley"))
        YoyoPulley->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/SDashWheel.bin", SCOPE_STAGE);

    Mod.Super(YoyoPulley->classID, SUPER_STAGELOAD, NULL);
}
