#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Press.h"

ObjectPress *Press;

void Press_StageLoad(void)
{
    if (CheckUnlock("Press"))
        Press->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/Press.bin", SCOPE_STAGE);

    Mod.Super(Press->classID, SUPER_STAGELOAD, NULL);
}
