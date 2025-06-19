#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Caterkiller.h"

ObjectCaterkiller *Caterkiller;

void Caterkiller_StageLoad(void)
{
    if (CheckUnlock("Caterkiller"))
        Caterkiller->aniFrames = RSDK.LoadSpriteAnimation("MMZ/Caterkiller.bin", SCOPE_STAGE);

    Mod.Super(Caterkiller->classID, SUPER_STAGELOAD, NULL);
}
