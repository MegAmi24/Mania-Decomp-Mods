#include "GameAPI/Game.h"
#include "ContinuePlayer.h"
#include "Player.h"

ObjectContinuePlayer *ContinuePlayer;

void ContinuePlayer_StageLoad(void)
{
    RSDK_THIS(ContinuePlayer);

    Mod.Super(ContinuePlayer->classID, SUPER_STAGELOAD, NULL);

    Player_RandomizePalettes();
}
