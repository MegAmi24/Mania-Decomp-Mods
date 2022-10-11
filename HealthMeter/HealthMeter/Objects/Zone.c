#include "GameAPI/Game.h"
#include "Zone.h"
#include "Player.h"

ObjectZone *Zone;

void Zone_State_ReloadScene_Hook(void)
{
    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    Mod_Player->health    = player1->health;
}