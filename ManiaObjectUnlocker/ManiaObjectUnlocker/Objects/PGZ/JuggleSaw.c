#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "JuggleSaw.h"

ObjectJuggleSaw *JuggleSaw;

// 🦀 crab in da mod

void JuggleSaw_StageLoad(void)
{
    if (CheckUnlock("JuggleSawPSZ1"))
        JuggleSaw->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/JuggleSaw.bin", SCOPE_STAGE);

    Mod.Super(JuggleSaw->classID, SUPER_STAGELOAD, NULL);
}
