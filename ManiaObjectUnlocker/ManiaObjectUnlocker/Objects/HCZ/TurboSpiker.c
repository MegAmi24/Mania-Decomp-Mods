#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "TurboSpiker.h"

ObjectTurboSpiker *TurboSpiker;

void TurboSpiker_StageLoad(void)
{
    if (CheckUnlock("TurboSpiker"))
        TurboSpiker->aniFrames = RSDK.LoadSpriteAnimation("HCZ/TurboSpiker.bin", SCOPE_STAGE);

    Mod.Super(TurboSpiker->classID, SUPER_STAGELOAD, NULL);
}
