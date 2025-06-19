#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Fireworm.h"

ObjectFireworm *Fireworm;

void Fireworm_StageLoad(void)
{
    if (CheckUnlock("FirewormLRZ1"))
        Fireworm->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/Fireworm.bin", SCOPE_STAGE);

    Mod.Super(Fireworm->classID, SUPER_STAGELOAD, NULL);
}
