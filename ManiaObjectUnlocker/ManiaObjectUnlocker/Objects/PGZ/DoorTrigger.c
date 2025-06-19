#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "DoorTrigger.h"

ObjectDoorTrigger *DoorTrigger;

void DoorTrigger_StageLoad(void)
{
    if (CheckUnlock("DoorTrigger"))
        DoorTrigger->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/DoorTrigger.bin", SCOPE_STAGE);

    Mod.Super(DoorTrigger->classID, SUPER_STAGELOAD, NULL);
}
