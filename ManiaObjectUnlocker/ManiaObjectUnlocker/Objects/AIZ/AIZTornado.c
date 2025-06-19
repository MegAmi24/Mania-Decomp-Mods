#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "AIZTornado.h"

ObjectAIZTornado *AIZTornado;

void AIZTornado_StageLoad(void)
{
    if (CheckUnlock("AIZTornado"))
        AIZTornado->aniFrames = RSDK.LoadSpriteAnimation("AIZ/AIZTornado.bin", SCOPE_STAGE);

    Mod.Super(AIZTornado->classID, SUPER_STAGELOAD, NULL);
}
