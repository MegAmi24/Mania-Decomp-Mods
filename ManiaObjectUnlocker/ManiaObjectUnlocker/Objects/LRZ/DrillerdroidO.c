#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "DrillerdroidO.h"

ObjectDrillerdroidO *DrillerdroidO;

void DrillerdroidO_StageLoad(void)
{
    if (CheckUnlock("DrillerdroidO"))
        DrillerdroidO->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/Drillerdroid.bin", SCOPE_STAGE);

    Mod.Super(DrillerdroidO->classID, SUPER_STAGELOAD, NULL);
}
