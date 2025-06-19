#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "SentryBug.h"

ObjectSentryBug *SentryBug;

void SentryBug_StageLoad(void)
{
    if (CheckUnlock("SentryBug"))
        SentryBug->aniFrames = RSDK.LoadSpriteAnimation("TMZ1/SentryBug.bin", SCOPE_STAGE);

    Mod.Super(SentryBug->classID, SUPER_STAGELOAD, NULL);
}
