#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Clapperboard.h"

ObjectClapperboard *Clapperboard;

void Clapperboard_StageLoad(void)
{
    Mod.Super(Clapperboard->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("ClapperboardSPZ1"))
        Clapperboard->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/Clapperboard.bin", SCOPE_STAGE);
}
