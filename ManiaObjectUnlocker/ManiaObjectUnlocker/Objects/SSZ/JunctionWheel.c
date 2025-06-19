#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "JunctionWheel.h"

ObjectJunctionWheel *JunctionWheel;

void JunctionWheel_StageLoad(void)
{
    if (CheckUnlock("JunctionWheel"))
        JunctionWheel->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/JunctionWheel.bin", SCOPE_STAGE);

    Mod.Super(JunctionWheel->classID, SUPER_STAGELOAD, NULL);
}
