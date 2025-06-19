#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "SP500.h"

ObjectSP500 *SP500;

void SP500_StageLoad(void)
{
    if (CheckUnlock("SP500"))
        SP500->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/SP500.bin", SCOPE_STAGE);

    Mod.Super(SP500->classID, SUPER_STAGELOAD, NULL);
}
