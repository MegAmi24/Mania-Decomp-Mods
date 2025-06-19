#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "PSZDoor.h"

ObjectPSZDoor *PSZDoor;

void PSZDoor_StageLoad(void)
{
    if (CheckUnlock("PSZDoor"))
        PSZDoor->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/PSZDoor.bin", SCOPE_STAGE);

    Mod.Super(PSZDoor->classID, SUPER_STAGELOAD, NULL);
}
