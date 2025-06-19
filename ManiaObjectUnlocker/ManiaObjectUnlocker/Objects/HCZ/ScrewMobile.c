#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "ScrewMobile.h"

ObjectScrewMobile *ScrewMobile;

void ScrewMobile_StageLoad(void)
{
    if (CheckUnlock("ScrewMobile"))
        ScrewMobile->aniFrames = RSDK.LoadSpriteAnimation("HCZ/ScrewMobile.bin", SCOPE_STAGE);

    Mod.Super(ScrewMobile->classID, SUPER_STAGELOAD, NULL);
}
