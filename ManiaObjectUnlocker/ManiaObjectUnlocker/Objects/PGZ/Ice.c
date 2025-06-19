#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Ice.h"

ObjectIce *Ice;

void Ice_StageLoad(void)
{
    if (CheckUnlock("IcePSZ1")) // PGZ1 doesn't have ice anywhere, likely leftover from an earlier revision
        Ice->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/Ice.bin", SCOPE_STAGE);

    Mod.Super(Ice->classID, SUPER_STAGELOAD, NULL);
}
