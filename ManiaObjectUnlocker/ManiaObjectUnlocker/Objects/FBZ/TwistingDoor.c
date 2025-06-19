#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "TwistingDoor.h"

ObjectTwistingDoor *TwistingDoor;

void TwistingDoor_StageLoad(void)
{
    if (CheckUnlock("TwistingDoor"))
        TwistingDoor->aniFrames = RSDK.LoadSpriteAnimation("FBZ/TwistingDoor.bin", SCOPE_STAGE);

    Mod.Super(TwistingDoor->classID, SUPER_STAGELOAD, NULL);
}
