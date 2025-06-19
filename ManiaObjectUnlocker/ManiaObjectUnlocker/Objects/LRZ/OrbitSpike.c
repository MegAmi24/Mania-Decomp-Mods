#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "OrbitSpike.h"

ObjectOrbitSpike *OrbitSpike;

void OrbitSpike_StageLoad(void)
{
    if (CheckUnlock("OrbitSpikeLRZ1"))
        OrbitSpike->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/OrbitSpike.bin", SCOPE_STAGE);

    Mod.Super(OrbitSpike->classID, SUPER_STAGELOAD, NULL);
}
