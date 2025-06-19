#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "SpikeLog.h"

ObjectSpikeLog *SpikeLog;

void SpikeLog_StageLoad(void)
{
    if (CheckUnlock("SpikeLog"))
        SpikeLog->aniFrames = RSDK.LoadSpriteAnimation("GHZ/SpikeLog.bin", SCOPE_STAGE);

    Mod.Super(SpikeLog->classID, SUPER_STAGELOAD, NULL);
}
