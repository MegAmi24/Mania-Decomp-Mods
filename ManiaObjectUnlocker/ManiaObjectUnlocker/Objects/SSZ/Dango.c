#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Dango.h"

ObjectDango *Dango;

void Dango_StageLoad(void)
{
    if (CheckUnlock("DangoSSZ1"))
        Dango->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/Dango.bin", SCOPE_STAGE);

    Mod.Super(Dango->classID, SUPER_STAGELOAD, NULL);
}
