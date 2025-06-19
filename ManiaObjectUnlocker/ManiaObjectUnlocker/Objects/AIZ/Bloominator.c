#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Bloominator.h"

#if MANIA_USE_PLUS
ObjectBloominator *Bloominator;

void Bloominator_StageLoad(void)
{
    if (CheckUnlock("Bloominator"))
        Bloominator->aniFrames = RSDK.LoadSpriteAnimation("AIZ/Bloominator.bin", SCOPE_STAGE);

    Mod.Super(Bloominator->classID, SUPER_STAGELOAD, NULL);
}
#endif
