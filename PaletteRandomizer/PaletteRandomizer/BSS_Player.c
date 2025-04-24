#include "GameAPI/Game.h"
#include "BSS_Player.h"
#include "Player.h"

ObjectBSS_Player *BSS_Player;

void BSS_Player_StageLoad(void)
{
    RSDK_THIS(BSS_Player);

    Mod.Super(BSS_Player->classID, SUPER_STAGELOAD, NULL);

    Player_RandomizePalettes();
}
