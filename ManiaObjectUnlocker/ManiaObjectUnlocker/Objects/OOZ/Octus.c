#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Octus.h"

ObjectOctus *Octus;

void Octus_StageLoad(void)
{
    if (CheckUnlock("Octus"))
        Octus->aniFrames = RSDK.LoadSpriteAnimation("OOZ/Octus.bin", SCOPE_STAGE);

    Mod.Super(Octus->classID, SUPER_STAGELOAD, NULL);
}
