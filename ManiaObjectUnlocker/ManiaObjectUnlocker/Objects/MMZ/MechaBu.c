#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "MechaBu.h"

ObjectMechaBu *MechaBu;

void MechaBu_StageLoad(void)
{
    if (CheckUnlock("MechaBu"))
        MechaBu->aniFrames = RSDK.LoadSpriteAnimation("MMZ/MechaBu.bin", SCOPE_STAGE);

    Mod.Super(MechaBu->classID, SUPER_STAGELOAD, NULL);
}
