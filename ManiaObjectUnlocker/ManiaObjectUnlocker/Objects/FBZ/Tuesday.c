#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Tuesday.h"

ObjectTuesday *Tuesday;

void Tuesday_StageLoad(void)
{
    if (CheckUnlock("Tuesday"))
        Tuesday->aniFrames = RSDK.LoadSpriteAnimation("FBZ/Tuesday.bin", SCOPE_STAGE);

    Mod.Super(Tuesday->classID, SUPER_STAGELOAD, NULL);
}
