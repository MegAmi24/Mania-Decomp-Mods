#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "LaunchSpring.h"

ObjectLaunchSpring *LaunchSpring;

void LaunchSpring_StageLoad(void)
{
    if (CheckUnlock("LaunchSpringSSZ1"))
        LaunchSpring->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/LaunchSpring.bin", SCOPE_STAGE);

    Mod.Super(LaunchSpring->classID, SUPER_STAGELOAD, NULL);
}
