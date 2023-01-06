#include "GameAPI/Game.h"
#include "DebugMode.h"
#include "Player.h"

ObjectDebugMode *DebugMode;

void DebugMode_Update(void)
{
    RSDK_THIS(DebugMode);

    if (ControllerInfo[CONT_P1].keyStart.press) {
        // Do this so we can access the player variables
        RSDK_THIS(Player);
        RSDK.SetEngineState(ENGINESTATE_FROZEN);
        SceneInfo->timeEnabled = false;
        if (self->camera) {
            self->scrollDelay   = 2;
            self->camera->state = StateMachine_None;
        }

        RSDK.SetScene("Presentation", "Level Select");
        Zone_StartFadeOut_MusicFade(10, 0x000000);
    }
    else
        Mod.Super(DebugMode->classID, SUPER_UPDATE, NULL);
}