#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Blastoid.h"

ObjectBlastoid *Blastoid;

void Blastoid_StageLoad(void)
{
    if (CheckUnlock("Blastoid"))
        Blastoid->aniFrames = RSDK.LoadSpriteAnimation("HCZ/Blastoid.bin", SCOPE_STAGE);

    Mod.Super(Blastoid->classID, SUPER_STAGELOAD, NULL);
}
