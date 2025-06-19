#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Jawz.h"

ObjectJawz *Jawz;

void Jawz_StageLoad(void)
{
    if (CheckUnlock("Jawz"))
        Jawz->aniFrames = RSDK.LoadSpriteAnimation("HCZ/Jawz.bin", SCOPE_STAGE);

    Mod.Super(Jawz->classID, SUPER_STAGELOAD, NULL);
}
