#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Aquis.h"

ObjectAquis *Aquis;

void Aquis_StageLoad(void)
{
    if (CheckUnlock("Aquis"))
        Aquis->aniFrames = RSDK.LoadSpriteAnimation("OOZ/Aquis.bin", SCOPE_STAGE);

    Mod.Super(Aquis->classID, SUPER_STAGELOAD, NULL);
}
