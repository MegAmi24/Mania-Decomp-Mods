#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "HotaruMKII.h"

ObjectHotaruMKII *HotaruMKII;

void HotaruMKII_StageLoad(void)
{
    if (CheckUnlock("HotaruMKIISSZ1"))
        HotaruMKII->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/HotaruMKII.bin", SCOPE_STAGE);
    
    Mod.Super(HotaruMKII->classID, SUPER_STAGELOAD, NULL);
}
