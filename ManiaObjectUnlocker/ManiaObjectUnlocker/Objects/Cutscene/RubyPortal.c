#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "RubyPortal.h"

ObjectRubyPortal *RubyPortal;

void RubyPortal_StageLoad(void)
{
#if MANIA_USE_PLUS
    if (CheckUnlock("RubyPortalAIZ"))
        RubyPortal->aniFrames = RSDK.LoadSpriteAnimation("AIZ/Portal.bin", SCOPE_STAGE);
#else // preplus has an explicit check
    if (CheckUnlock("RubyPortalTMZ2"))
        RubyPortal->aniFrames = RSDK.LoadSpriteAnimation("TMZ1/Portal.bin", SCOPE_STAGE);
#endif

    Mod.Super(RubyPortal->classID, SUPER_STAGELOAD, NULL);

#if MANIA_USE_PLUS
    if (CheckUnlock("RubyPortalTMZ2"))
        RubyPortal->aniFrames = RSDK.LoadSpriteAnimation("TMZ1/Portal.bin", SCOPE_STAGE);
#endif
}
