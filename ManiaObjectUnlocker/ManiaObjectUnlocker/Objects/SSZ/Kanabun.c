#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Kanabun.h"

ObjectKanabun *Kanabun;

void Kanabun_StageLoad(void)
{
    if (CheckUnlock("KanabunSSZ1"))
        Kanabun->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/Kanabun.bin", SCOPE_STAGE);

    Mod.Super(Kanabun->classID, SUPER_STAGELOAD, NULL);
}
