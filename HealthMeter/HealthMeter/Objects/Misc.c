#include "GameAPI/Game.h"
#include "Misc.h"
#include "Player.h"
#include "../ModConfig.h"

ObjectTitleCard *TitleCard;
ObjectZone *Zone;

void Zone_TitleCard_SupressCB_Hook(void) { Mod_Player->health = config.StartingHealth; }

void Zone_State_ReloadScene_Hook(void)
{
    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    Mod_Player->health    = player1->health;
}