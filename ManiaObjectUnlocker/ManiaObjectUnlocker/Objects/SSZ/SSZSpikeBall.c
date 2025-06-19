#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "SSZSpikeBall.h"

ObjectSSZSpikeBall *SSZSpikeBall;

void SSZSpikeBall_StageLoad(void)
{
    Mod.Super(SSZSpikeBall->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("SSZSpikeBallSSZ1"))
        SSZSpikeBall->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/SpikeBall.bin", SCOPE_STAGE);
}
