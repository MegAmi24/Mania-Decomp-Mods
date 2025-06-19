#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "PushSpring.h"

ObjectPushSpring *PushSpring;

void PushSpring_StageLoad(void)
{
    if (CheckUnlock("PushSpring"))
        PushSpring->aniFrames = RSDK.LoadSpriteAnimation("OOZ/PushSpring.bin", SCOPE_STAGE);

    Mod.Super(PushSpring->classID, SUPER_STAGELOAD, NULL);
}
