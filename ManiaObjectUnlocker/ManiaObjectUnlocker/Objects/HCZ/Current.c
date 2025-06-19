#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Current.h"

ObjectCurrent *Current;

void Current_StageLoad(void)
{
    Mod.Super(Current->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("CurrentFBZ"))
        Current->aniFrames = RSDK.LoadSpriteAnimation("FBZ/Current.bin", SCOPE_STAGE);
}
