#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Orbinaut.h"

ObjectOrbinaut *Orbinaut;

void Orbinaut_StageLoad(void)
{
    if (CheckUnlock("Orbinaut"))
        Orbinaut->aniFrames = RSDK.LoadSpriteAnimation("MMZ/Orbinaut.bin", SCOPE_STAGE);

    Mod.Super(Orbinaut->classID, SUPER_STAGELOAD, NULL);
}
