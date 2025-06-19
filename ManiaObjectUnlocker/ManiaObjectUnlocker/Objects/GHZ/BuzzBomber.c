#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "BuzzBomber.h"

ObjectBuzzBomber *BuzzBomber;

void BuzzBomber_StageLoad(void)
{
    if (CheckUnlock("BuzzBomberGHZ"))
        BuzzBomber->aniFrames = RSDK.LoadSpriteAnimation("GHZ/BuzzBomber.bin", SCOPE_STAGE);

    Mod.Super(BuzzBomber->classID, SUPER_STAGELOAD, NULL);
}
