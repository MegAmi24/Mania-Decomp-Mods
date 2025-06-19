#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Rexon.h"

ObjectRexon *Rexon;

void Rexon_StageLoad(void)
{
    if (CheckUnlock("RexonLRZ1"))
        Rexon->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/Rexon.bin", SCOPE_STAGE);
    
    Mod.Super(Rexon->classID, SUPER_STAGELOAD, NULL);
}
