#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "TeeterTotter.h"

ObjectTeeterTotter *TeeterTotter;

void TeeterTotter_StageLoad(void)
{
    if (CheckUnlock("TeeterTotter"))
        TeeterTotter->aniFrames = RSDK.LoadSpriteAnimation("TMZ1/TeeterTotter.bin", SCOPE_STAGE);

    Mod.Super(TeeterTotter->classID, SUPER_STAGELOAD, NULL);
}
