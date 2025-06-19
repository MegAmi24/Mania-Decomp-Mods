#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Jellygnite.h"

ObjectJellygnite *Jellygnite;

void Jellygnite_StageLoad(void)
{
    if (CheckUnlock("JellygniteHCZ"))
        Jellygnite->aniFrames = RSDK.LoadSpriteAnimation("HCZ/Jellygnite.bin", SCOPE_STAGE);

    Mod.Super(Jellygnite->classID, SUPER_STAGELOAD, NULL);
}
