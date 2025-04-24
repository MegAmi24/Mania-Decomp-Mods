#include "GameAPI/Game.h"
#include "MenuSetup.h"
#include "Player.h"

ObjectMenuSetup *MenuSetup;

void MenuSetup_StageLoad(void)
{
    RSDK_THIS(MenuSetup);

    Mod.Super(MenuSetup->classID, SUPER_STAGELOAD, NULL);

    Player_RandomizePalettes();
}
