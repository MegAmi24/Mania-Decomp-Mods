#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "PetalPile.h"

ObjectPetalPile *PetalPile;

void PetalPile_StageLoad(void)
{
    if (CheckUnlock("PetalPilePSZ1"))
        PetalPile->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/Petal.bin", SCOPE_STAGE);
    else if (CheckUnlock("PetalPilePSZ2"))
        PetalPile->aniFrames = RSDK.LoadSpriteAnimation("PSZ2/Petal.bin", SCOPE_STAGE);

    Mod.Super(PetalPile->classID, SUPER_STAGELOAD, NULL);
}
