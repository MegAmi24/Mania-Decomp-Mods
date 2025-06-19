#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "MagnetSphere.h"

ObjectMagnetSphere *MagnetSphere;

void MagnetSphere_StageLoad(void)
{
    if (CheckUnlock("MagnetSphere"))
        MagnetSphere->aniFrames = RSDK.LoadSpriteAnimation("TMZ1/MagnetSphere.bin", SCOPE_STAGE);

    Mod.Super(MagnetSphere->classID, SUPER_STAGELOAD, NULL);
}
