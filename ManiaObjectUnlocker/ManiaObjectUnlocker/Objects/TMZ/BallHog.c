#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "BallHog.h"

ObjectBallHog *BallHog;

void BallHog_StageLoad(void)
{
    if (CheckUnlock("BallHog"))
        BallHog->aniFrames = RSDK.LoadSpriteAnimation("TMZ1/BallHog.bin", SCOPE_STAGE);

    Mod.Super(BallHog->classID, SUPER_STAGELOAD, NULL);
}
