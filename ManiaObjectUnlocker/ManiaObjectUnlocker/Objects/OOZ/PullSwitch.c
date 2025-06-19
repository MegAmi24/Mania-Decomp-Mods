#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "PullSwitch.h"

ObjectPullSwitch *PullSwitch;

void PullSwitch_StageLoad(void)
{
    if (CheckUnlock("PullSwitch"))
        PullSwitch->aniFrames = RSDK.LoadSpriteAnimation("OOZ/PullSwitch.bin", SCOPE_STAGE);

    Mod.Super(PullSwitch->classID, SUPER_STAGELOAD, NULL);
}
