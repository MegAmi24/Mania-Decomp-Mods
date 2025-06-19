#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Chopper.h"

ObjectChopper *Chopper;

void Chopper_StageLoad(void)
{
    if (CheckUnlock("Chopper"))
        Chopper->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Chopper.bin", SCOPE_STAGE);

    Mod.Super(Chopper->classID, SUPER_STAGELOAD, NULL);
}
