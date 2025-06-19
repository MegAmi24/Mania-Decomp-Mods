#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Ball.h"

ObjectBall *Ball;

void Ball_StageLoad(void)
{
    if (CheckUnlock("Ball"))
        Ball->aniFrames = RSDK.LoadSpriteAnimation("CPZ/Ball.bin", SCOPE_STAGE);

    Mod.Super(Ball->classID, SUPER_STAGELOAD, NULL);
}
