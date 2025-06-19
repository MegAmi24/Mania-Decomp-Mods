#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "FlameSpring.h"

ObjectFlameSpring *FlameSpring;

void FlameSpring_StageLoad(void)
{
    if (CheckUnlock("FlameSpring"))
        FlameSpring->aniFrames = RSDK.LoadSpriteAnimation("FBZ/FlameSpring.bin", SCOPE_STAGE);

    Mod.Super(FlameSpring->classID, SUPER_STAGELOAD, NULL);
}
