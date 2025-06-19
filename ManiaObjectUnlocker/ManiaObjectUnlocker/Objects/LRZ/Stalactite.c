#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Stalactite.h"

ObjectStalactite *Stalactite;

void Stalactite_StageLoad(void)
{
    if (CheckUnlock("Stalactite"))
        Stalactite->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/Stalactite.bin", SCOPE_STAGE);

    Mod.Super(Stalactite->classID, SUPER_STAGELOAD, NULL);
}
