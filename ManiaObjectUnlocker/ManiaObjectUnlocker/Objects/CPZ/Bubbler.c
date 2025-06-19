#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Bubbler.h"

ObjectBubbler *Bubbler;

void Bubbler_StageLoad(void)
{
    if (CheckUnlock("Bubbler"))
        Bubbler->aniFrames = RSDK.LoadSpriteAnimation("CPZ/Bubbler.bin", SCOPE_STAGE);

    Mod.Super(Bubbler->classID, SUPER_STAGELOAD, NULL);
}
