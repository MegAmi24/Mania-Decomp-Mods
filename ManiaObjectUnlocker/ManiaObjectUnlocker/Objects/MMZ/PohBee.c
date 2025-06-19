#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "PohBee.h"

ObjectPohBee *PohBee;

void PohBee_StageLoad(void)
{
    if (CheckUnlock("PohBee"))
        PohBee->aniFrames = RSDK.LoadSpriteAnimation("MMZ/PohBee.bin", SCOPE_STAGE);

    Mod.Super(PohBee->classID, SUPER_STAGELOAD, NULL);
}
