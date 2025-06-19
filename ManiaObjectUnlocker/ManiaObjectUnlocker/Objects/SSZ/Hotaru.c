#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Hotaru.h"

ObjectHotaru *Hotaru;

void Hotaru_StageLoad(void)
{
    if (CheckUnlock("HotaruSSZ1"))
        Hotaru->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/Hotaru.bin", SCOPE_STAGE);

    Mod.Super(Hotaru->classID, SUPER_STAGELOAD, NULL);
}
