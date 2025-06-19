#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Crate.h"

ObjectCrate *Crate;

void Crate_StageLoad(void)
{
    if (CheckUnlock("Crate"))
        Crate->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/Crate.bin", SCOPE_STAGE);

    Mod.Super(Crate->classID, SUPER_STAGELOAD, NULL);
}
