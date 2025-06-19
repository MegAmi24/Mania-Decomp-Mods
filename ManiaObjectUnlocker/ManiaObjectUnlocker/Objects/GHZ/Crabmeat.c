#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Crabmeat.h"

ObjectCrabmeat *Crabmeat;

void Crabmeat_StageLoad(void)
{
    if (CheckUnlock("Crabmeat"))
        Crabmeat->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Crabmeat.bin", SCOPE_STAGE);

    Mod.Super(Crabmeat->classID, SUPER_STAGELOAD, NULL);
}
