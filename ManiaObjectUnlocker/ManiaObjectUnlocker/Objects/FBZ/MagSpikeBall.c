#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "MagSpikeBall.h"

ObjectMagSpikeBall *MagSpikeBall;

void MagSpikeBall_StageLoad(void)
{
    if (CheckUnlock("MagSpikeBall"))
        MagSpikeBall->aniFrames = RSDK.LoadSpriteAnimation("FBZ/MagSpikeBall.bin", SCOPE_STAGE);

    Mod.Super(MagSpikeBall->classID, SUPER_STAGELOAD, NULL);
}
