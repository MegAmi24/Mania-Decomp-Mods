#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Fireball.h"

ObjectFireball *Fireball;

void Fireball_StageLoad(void)
{
    if (CheckUnlock("Fireball"))
        Fireball->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Fireball.bin", SCOPE_STAGE);

    Mod.Super(Fireball->classID, SUPER_STAGELOAD, NULL);
}
