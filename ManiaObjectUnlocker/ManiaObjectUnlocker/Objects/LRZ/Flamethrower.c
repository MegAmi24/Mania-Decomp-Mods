#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Flamethrower.h"

ObjectFlamethrower *Flamethrower;

void Flamethrower_StageLoad(void)
{
    if (CheckUnlock("FlamethrowerLRZ2"))
        Flamethrower->aniFrames = RSDK.LoadSpriteAnimation("LRZ2/Flamethrower.bin", SCOPE_STAGE);

    Mod.Super(Flamethrower->classID, SUPER_STAGELOAD, NULL);
}
