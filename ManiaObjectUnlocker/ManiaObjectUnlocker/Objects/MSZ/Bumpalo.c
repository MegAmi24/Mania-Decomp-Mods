#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Bumpalo.h"

ObjectBumpalo *Bumpalo;

void Bumpalo_StageLoad(void)
{
    if (CheckUnlock("Bumpalo"))
        Bumpalo->aniFrames = RSDK.LoadSpriteAnimation("MSZ/Bumpalo.bin", SCOPE_STAGE);

    Mod.Super(Bumpalo->classID, SUPER_STAGELOAD, NULL);
}
