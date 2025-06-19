#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "DirectorChair.h"

ObjectDirectorChair *DirectorChair;

void DirectorChair_StageLoad(void)
{
    if (CheckUnlock("DirectorChair"))
        DirectorChair->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/DirectorChair.bin", SCOPE_STAGE);

    Mod.Super(DirectorChair->classID, SUPER_STAGELOAD, NULL);
}
