#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "MatryoshkaBom.h"

ObjectMatryoshkaBom *MatryoshkaBom;

void MatryoshkaBom_StageLoad(void)
{
    if (CheckUnlock("MatryoshkaBom"))
        MatryoshkaBom->aniFrames = RSDK.LoadSpriteAnimation("MMZ/MatryoshkaBom.bin", SCOPE_STAGE);

    Mod.Super(MatryoshkaBom->classID, SUPER_STAGELOAD, NULL);
}
