#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "RotatingSpikes.h"

ObjectRotatingSpikes *RotatingSpikes;

void RotatingSpikes_StageLoad(void)
{
    if (CheckUnlock("RotatingSpikesMSZ"))
        RotatingSpikes->aniFrames = RSDK.LoadSpriteAnimation("MSZ/RotatingSpikes.bin", SCOPE_STAGE);
    else if (CheckUnlock("RotatingSpikesSSZ1"))
        RotatingSpikes->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/RotatingSpikes.bin", SCOPE_STAGE);

    Mod.Super(RotatingSpikes->classID, SUPER_STAGELOAD, NULL);
}
