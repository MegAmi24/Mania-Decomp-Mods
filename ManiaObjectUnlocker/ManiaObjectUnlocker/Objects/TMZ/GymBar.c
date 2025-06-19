#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "GymBar.h"

ObjectGymBar *GymBar;

void GymBar_StageLoad(void)
{
    if (CheckUnlock("GymBar"))
        GymBar->aniFrames = RSDK.LoadSpriteAnimation("TMZ1/GymBar.bin", SCOPE_STAGE);

    Mod.Super(GymBar->classID, SUPER_STAGELOAD, NULL);
}
