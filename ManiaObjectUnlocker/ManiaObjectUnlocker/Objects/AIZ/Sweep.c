#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Sweep.h"

ObjectSweep *Sweep;

void Sweep_StageLoad(void)
{
    if (CheckUnlock("SweepCPZ"))
        Sweep->aniFrames = RSDK.LoadSpriteAnimation("CPZ/Sweep.bin", SCOPE_STAGE);
#if MANIA_USE_PLUS
    else if (CheckUnlock("SweepAIZ"))
        Sweep->aniFrames = RSDK.LoadSpriteAnimation("AIZ/Sweep.bin", SCOPE_STAGE);
#endif

    Mod.Super(Sweep->classID, SUPER_STAGELOAD, NULL);
}
