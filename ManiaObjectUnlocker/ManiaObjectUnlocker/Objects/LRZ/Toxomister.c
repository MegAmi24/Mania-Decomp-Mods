#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Toxomister.h"

ObjectToxomister *Toxomister;

void Toxomister_StageLoad(void)
{
    if (CheckUnlock("ToxomisterLRZ1"))
        Toxomister->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/Toxomister.bin", SCOPE_STAGE);

    Mod.Super(Toxomister->classID, SUPER_STAGELOAD, NULL);
}
