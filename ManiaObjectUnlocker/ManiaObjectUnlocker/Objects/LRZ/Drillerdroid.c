#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Drillerdroid.h"

ObjectDrillerdroid *Drillerdroid;

void Drillerdroid_StageLoad(void)
{
    if (CheckUnlock("Drillerdroid"))
        Drillerdroid->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/Drillerdroid.bin", SCOPE_STAGE);

    Mod.Super(Drillerdroid->classID, SUPER_STAGELOAD, NULL);
}
