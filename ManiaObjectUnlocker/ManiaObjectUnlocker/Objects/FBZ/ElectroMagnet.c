#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "ElectroMagnet.h"

ObjectElectroMagnet *ElectroMagnet;

void ElectroMagnet_StageLoad(void)
{
    if (CheckUnlock("ElectroMagnet"))
        ElectroMagnet->aniFrames = RSDK.LoadSpriteAnimation("FBZ/ElectroMagnet.bin", SCOPE_STAGE);

    Mod.Super(ElectroMagnet->classID, SUPER_STAGELOAD, NULL);
}
