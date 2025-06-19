#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Sol.h"

ObjectSol *Sol;

void Sol_StageLoad(void)
{
    if (CheckUnlock("Sol"))
        Sol->aniFrames = RSDK.LoadSpriteAnimation("OOZ/Sol.bin", SCOPE_STAGE);

    Mod.Super(Sol->classID, SUPER_STAGELOAD, NULL);
}
