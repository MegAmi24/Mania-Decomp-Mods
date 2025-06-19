#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Woodrow.h"

ObjectWoodrow *Woodrow;

void Woodrow_StageLoad(void)
{
    if (CheckUnlock("WoodrowPSZ1"))
        Woodrow->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/Woodrow.bin", SCOPE_STAGE);

    Mod.Super(Woodrow->classID, SUPER_STAGELOAD, NULL);
}
