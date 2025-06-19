#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Motobug.h"

ObjectMotobug *Motobug;

void Motobug_StageLoad(void)
{
    if (CheckUnlock("MotobugGHZ"))
        Motobug->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Motobug.bin", SCOPE_STAGE);

    Mod.Super(Motobug->classID, SUPER_STAGELOAD, NULL);
}
