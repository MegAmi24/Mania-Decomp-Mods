#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Scarab.h"

ObjectScarab *Scarab;

void Scarab_StageLoad(void)
{
    if (CheckUnlock("Scarab"))
        Scarab->aniFrames = RSDK.LoadSpriteAnimation("MMZ/Scarab.bin", SCOPE_STAGE);

    Mod.Super(Scarab->classID, SUPER_STAGELOAD, NULL);
}
