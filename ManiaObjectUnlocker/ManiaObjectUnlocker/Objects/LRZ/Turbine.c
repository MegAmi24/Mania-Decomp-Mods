#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Turbine.h"

ObjectTurbine *Turbine;

void Turbine_StageLoad(void)
{
    if (CheckUnlock("Turbine"))
        Turbine->aniFrames = RSDK.LoadSpriteAnimation("LRZ2/Turbine.bin", SCOPE_STAGE);

    Mod.Super(Turbine->classID, SUPER_STAGELOAD, NULL);
}
