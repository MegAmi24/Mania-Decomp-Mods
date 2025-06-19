#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Ink.h"

ObjectInk *Ink;

void Ink_StageLoad(void)
{
    if (CheckUnlock("Ink"))
        Ink->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/Ink.bin", SCOPE_STAGE);

    Mod.Super(Ink->classID, SUPER_STAGELOAD, NULL);
}
