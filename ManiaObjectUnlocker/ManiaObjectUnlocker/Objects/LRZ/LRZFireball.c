#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "LRZFireball.h"

ObjectLRZFireball *LRZFireball;

void LRZFireball_StageLoad(void)
{
    if (CheckUnlock("LRZFireball"))
        LRZFireball->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/LRZFireball.bin", SCOPE_STAGE);

    Mod.Super(LRZFireball->classID, SUPER_STAGELOAD, NULL);
}
