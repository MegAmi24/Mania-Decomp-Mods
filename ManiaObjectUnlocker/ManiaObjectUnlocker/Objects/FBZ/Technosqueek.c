#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Technosqueek.h"

ObjectTechnosqueek *Technosqueek;

void Technosqueek_StageLoad(void)
{
    if (CheckUnlock("Technosqueek"))
        Technosqueek->aniFrames = RSDK.LoadSpriteAnimation("FBZ/Technosqueek.bin", SCOPE_STAGE);

    Mod.Super(Technosqueek->classID, SUPER_STAGELOAD, NULL);
}
