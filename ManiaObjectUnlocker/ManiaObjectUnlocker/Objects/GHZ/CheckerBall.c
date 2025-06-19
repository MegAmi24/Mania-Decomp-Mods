#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "CheckerBall.h"

ObjectCheckerBall *CheckerBall;

void CheckerBall_StageLoad(void)
{
    if (CheckUnlock("CheckerBallGHZ"))
        CheckerBall->aniFrames = RSDK.LoadSpriteAnimation("GHZ/CheckerBall.bin", SCOPE_STAGE);

    Mod.Super(CheckerBall->classID, SUPER_STAGELOAD, NULL);
}
