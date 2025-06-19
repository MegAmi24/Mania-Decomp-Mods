#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Canista.h"

ObjectCanista *Canista;

void Canista_StageLoad(void)
{
    if (CheckUnlock("CanistaSPZ1"))
        Canista->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/Canista.bin", SCOPE_STAGE);
    else if (CheckUnlock("CanistaSPZ2"))
        Canista->aniFrames = RSDK.LoadSpriteAnimation("SPZ2/Canista.bin", SCOPE_STAGE);

    Mod.Super(Canista->classID, SUPER_STAGELOAD, NULL);
}
