#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "OneWayDoor.h"

ObjectOneWayDoor *OneWayDoor;

void OneWayDoor_StageLoad(void)
{
    if (CheckUnlock("OneWayDoorMMZ"))
        OneWayDoor->aniFrames = RSDK.LoadSpriteAnimation("MMZ/OneWayDoor.bin", SCOPE_STAGE);
    else if (CheckUnlock("OneWayDoorCPZ"))
        OneWayDoor->aniFrames = RSDK.LoadSpriteAnimation("CPZ/OneWayDoor.bin", SCOPE_STAGE);

    Mod.Super(OneWayDoor->classID, SUPER_STAGELOAD, NULL);
}
