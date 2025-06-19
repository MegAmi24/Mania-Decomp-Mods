#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "PrintBlock.h"

ObjectPrintBlock *PrintBlock;

void PrintBlock_StageLoad(void)
{
    if (CheckUnlock("PrintBlock"))
        PrintBlock->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/PrintBlock.bin", SCOPE_STAGE);

    Mod.Super(PrintBlock->classID, SUPER_STAGELOAD, NULL);
}
