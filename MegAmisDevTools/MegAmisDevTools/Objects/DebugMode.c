#include "GameAPI/Game.h"
#include "DebugMode.h"
#include "Misc.h"

ObjectDebugMode *DebugMode;

void DebugMode_Update(void)
{
    RSDK_THIS(DebugMode);

    // Don't remove the act transition
    ObjectZone *Zone             = Mod.FindObject("Zone");
    StateMachine(storedFinishCB) = Zone->stageFinishCallback;
    Mod.Super(DebugMode->classID, SUPER_UPDATE, NULL);
    Zone->stageFinishCallback = storedFinishCB;
}