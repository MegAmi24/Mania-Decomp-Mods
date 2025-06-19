#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Pointdexter.h"

ObjectPointdexter *Pointdexter;

void Pointdexter_StageLoad(void)
{
    if (CheckUnlock("Pointdexter"))
        Pointdexter->aniFrames = RSDK.LoadSpriteAnimation("HCZ/Pointdexter.bin", SCOPE_STAGE);

    Mod.Super(Pointdexter->classID, SUPER_STAGELOAD, NULL);
}
