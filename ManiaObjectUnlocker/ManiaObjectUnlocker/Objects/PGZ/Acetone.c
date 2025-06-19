#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Acetone.h"

ObjectAcetone *Acetone;

void Acetone_StageLoad(void)
{
    if (CheckUnlock("Acetone"))
        Acetone->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/Acetone.bin", SCOPE_STAGE);

    Mod.Super(Acetone->classID, SUPER_STAGELOAD, NULL);
}
