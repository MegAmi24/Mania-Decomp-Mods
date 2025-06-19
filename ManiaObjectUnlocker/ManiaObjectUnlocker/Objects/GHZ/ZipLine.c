#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "ZipLine.h"

ObjectZipLine *ZipLine;

void ZipLine_StageLoad(void)
{
    if (CheckUnlock("ZipLine"))
        ZipLine->aniFrames = RSDK.LoadSpriteAnimation("GHZ/ZipLine.bin", SCOPE_STAGE);

    Mod.Super(ZipLine->classID, SUPER_STAGELOAD, NULL);
}
