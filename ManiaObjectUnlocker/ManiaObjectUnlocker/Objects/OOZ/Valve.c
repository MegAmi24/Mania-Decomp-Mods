#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Valve.h"

ObjectValve *Valve;

void Valve_StageLoad(void)
{
    if (CheckUnlock("Valve"))
        Valve->aniFrames = RSDK.LoadSpriteAnimation("OOZ/Valve.bin", SCOPE_STAGE);

    Mod.Super(Valve->classID, SUPER_STAGELOAD, NULL);
}
