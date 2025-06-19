#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "LRZRockPile.h"

ObjectLRZRockPile *LRZRockPile;

void LRZRockPile_StageLoad(void)
{
    if (CheckUnlock("LRZRockPileLRZ1")) {
        LRZRockPile->aniFrames      = RSDK.LoadSpriteAnimation("LRZ1/LRZRockPile.bin", SCOPE_STAGE);
        LRZRockPile->particleFrames = RSDK.LoadSpriteAnimation("LRZ1/Particles.bin", SCOPE_STAGE);

        LRZRockPile->hitboxWall.left   = -16;
        LRZRockPile->hitboxWall.top    = -40;
        LRZRockPile->hitboxWall.right  = 16;
        LRZRockPile->hitboxWall.bottom = 40;
    }

    Mod.Super(LRZRockPile->classID, SUPER_STAGELOAD, NULL);
}
