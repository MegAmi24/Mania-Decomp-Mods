#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "FlowerPod.h"

ObjectFlowerPod *FlowerPod;

void FlowerPod_StageLoad(void)
{
    if (CheckUnlock("FlowerPod"))
        FlowerPod->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/FlowerPod.bin", SCOPE_STAGE);

    Mod.Super(FlowerPod->classID, SUPER_STAGELOAD, NULL);
}
