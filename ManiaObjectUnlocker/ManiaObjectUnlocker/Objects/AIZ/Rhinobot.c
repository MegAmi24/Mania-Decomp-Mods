#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Rhinobot.h"

#if MANIA_USE_PLUS
ObjectRhinobot *Rhinobot;

void Rhinobot_StageLoad(void)
{
    if (CheckUnlock("Rhinobot"))
        Rhinobot->aniFrames = RSDK.LoadSpriteAnimation("AIZ/Rhinobot.bin", SCOPE_STAGE);

    Mod.Super(Rhinobot->classID, SUPER_STAGELOAD, NULL);
}
#endif
