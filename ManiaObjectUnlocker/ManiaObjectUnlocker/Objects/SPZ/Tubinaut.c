#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Tubinaut.h"

ObjectTubinaut *Tubinaut;

void Tubinaut_StageLoad(void)
{
    if (CheckUnlock("TubinautSPZ1"))
        Tubinaut->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/Tubinaut.bin", SCOPE_STAGE);

    Mod.Super(Tubinaut->classID, SUPER_STAGELOAD, NULL);
}
