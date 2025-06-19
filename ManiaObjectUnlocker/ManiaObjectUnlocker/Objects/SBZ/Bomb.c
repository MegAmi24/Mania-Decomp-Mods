#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Bomb.h"

ObjectBomb *Bomb;

void Bomb_StageLoad(void)
{
    if (CheckUnlock("Bomb"))
        Bomb->aniFrames = RSDK.LoadSpriteAnimation("MMZ/Bomb.bin", SCOPE_STAGE);

    Mod.Super(Bomb->classID, SUPER_STAGELOAD, NULL);
}
