#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "DCEvent.h"

ObjectDCEvent *DCEvent;

void DCEvent_StageLoad(void)
{
    if (CheckUnlock("DCEvent")) {
        DCEvent->aniFrames = RSDK.LoadSpriteAnimation("HCZ/DiveEggman.bin", SCOPE_STAGE);
        // Never actually used
        DCEvent->eggmanFrames = RSDK.LoadSpriteAnimation("Eggman/EggmanHCZ1.bin", SCOPE_STAGE);
    }

    Mod.Super(DCEvent->classID, SUPER_STAGELOAD, NULL);
}
