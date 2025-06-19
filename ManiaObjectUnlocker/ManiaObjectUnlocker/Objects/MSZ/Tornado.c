#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Tornado.h"

ObjectTornado *Tornado;

void Tornado_StageLoad(void)
{
    if (CheckUnlock("Tornado")) {
        Tornado->aniFrames = RSDK.LoadSpriteAnimation("MSZ/Tornado.bin", SCOPE_STAGE);
        if (!CHECK_CHARACTER_ID(ID_KNUCKLES, 1))
            Tornado->knuxFrames = RSDK.LoadSpriteAnimation("Players/KnuxCutsceneAIZ.bin", SCOPE_STAGE);
    }

    Mod.Super(Tornado->classID, SUPER_STAGELOAD, NULL);
}
