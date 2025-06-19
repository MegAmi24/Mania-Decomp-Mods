#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Newtron.h"

ObjectNewtron *Newtron;

void Newtron_StageLoad(void)
{
    if (CheckUnlock("Newtron"))
        Newtron->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Newtron.bin", SCOPE_STAGE);

    Mod.Super(Newtron->classID, SUPER_STAGELOAD, NULL);
}
