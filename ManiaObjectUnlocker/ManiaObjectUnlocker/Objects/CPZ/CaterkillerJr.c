#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "CaterkillerJr.h"

ObjectCaterkillerJr *CaterkillerJr;

void CaterkillerJr_StageLoad(void)
{
    if (CheckUnlock("CaterkillerJrCPZ"))
        CaterkillerJr->aniFrames = RSDK.LoadSpriteAnimation("CPZ/CaterkillerJr.bin", SCOPE_STAGE);
#if MANIA_USE_PLUS
    else if (CheckUnlock("CaterkillerJrAIZ"))
        CaterkillerJr->aniFrames = RSDK.LoadSpriteAnimation("AIZ/CaterkillerJr.bin", SCOPE_STAGE);
#endif

    Mod.Super(CaterkillerJr->classID, SUPER_STAGELOAD, NULL);
}
