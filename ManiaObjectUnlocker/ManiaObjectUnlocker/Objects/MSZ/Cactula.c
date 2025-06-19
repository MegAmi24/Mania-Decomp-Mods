#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Cactula.h"

ObjectCactula *Cactula;

void Cactula_StageLoad(void)
{
    if (CheckUnlock("Cactula"))
        Cactula->aniFrames = RSDK.LoadSpriteAnimation("MSZ/Cactula.bin", SCOPE_STAGE);

    Mod.Super(Cactula->classID, SUPER_STAGELOAD, NULL);
}
