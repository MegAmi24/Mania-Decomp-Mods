#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Batbrain.h"

ObjectBatbrain *Batbrain;

void Batbrain_StageLoad(void)
{
    if (CheckUnlock("Batbrain"))
        Batbrain->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Batbrain.bin", SCOPE_STAGE);

    Mod.Super(Batbrain->classID, SUPER_STAGELOAD, NULL);
}
