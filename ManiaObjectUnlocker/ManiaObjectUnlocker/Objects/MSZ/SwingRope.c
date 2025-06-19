#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "SwingRope.h"

ObjectSwingRope *SwingRope;

void SwingRope_StageLoad(void)
{
    if (CheckUnlock("SwingRopeMSZ"))
        SwingRope->aniFrames = RSDK.LoadSpriteAnimation("MSZ/SwingRope.bin", SCOPE_STAGE);
    else if (CheckUnlock("SwingRopeAIZ"))
        SwingRope->aniFrames = RSDK.LoadSpriteAnimation("AIZ/SwingRope.bin", SCOPE_STAGE);

    Mod.Super(SwingRope->classID, SUPER_STAGELOAD, NULL);
}
