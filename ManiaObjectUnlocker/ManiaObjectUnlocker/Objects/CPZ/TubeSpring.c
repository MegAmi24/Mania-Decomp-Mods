#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "TubeSpring.h"

ObjectTubeSpring *TubeSpring;

void TubeSpring_StageLoad(void)
{
    if (CheckUnlock("TubeSpringCPZ"))
        TubeSpring->aniFrames = RSDK.LoadSpriteAnimation("CPZ/TubeSpring.bin", SCOPE_STAGE);
    else if (CheckUnlock("TubeSpringFBZ"))
        TubeSpring->aniFrames = RSDK.LoadSpriteAnimation("FBZ/TubeSpring.bin", SCOPE_STAGE);

    Mod.Super(TubeSpring->classID, SUPER_STAGELOAD, NULL);
}
