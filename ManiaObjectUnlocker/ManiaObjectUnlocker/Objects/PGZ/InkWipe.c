#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "InkWipe.h"

ObjectInkWipe *InkWipe;

void InkWipe_StageLoad(void)
{
    if (CheckUnlock("InkWipe"))
        InkWipe->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/InkWipe.bin", SCOPE_STAGE);

    Mod.Super(InkWipe->classID, SUPER_STAGELOAD, NULL);
}
