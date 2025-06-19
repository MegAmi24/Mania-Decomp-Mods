#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "HangGlider.h"

#if MANIA_USE_PLUS
ObjectHangGlider *HangGlider;

void HangGlider_StageLoad(void)
{
    Mod.Super(HangGlider->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("HangGliderFBZ"))
        HangGlider->aniFrames = RSDK.LoadSpriteAnimation("FBZ/HangGlider.bin", SCOPE_STAGE);
}
#endif
