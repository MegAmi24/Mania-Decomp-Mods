#include "GameAPI/Game.h"
#include "Misc.h"
#include "Player.h"
#include "../ModConfig.h"

void (*CompSession_DeriveWinner)(int32 playerID, int32 finishType) = NULL;
Vector2 (*LRZConvItem_HandleLRZConvPhys)(void *e) = NULL;
StateMachine(Zone_TitleCard_SupressCB) = NULL;
StateMachine(Zone_State_ReloadScene) = NULL;

ObjectTitleCard *TitleCard;
ObjectZone *Zone;

void Zone_TitleCard_SupressCB_Hook(void) { Mod_Player->health = config.StartingHealth; }

void Zone_State_ReloadScene_Hook(void)
{
    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    Mod_Player->health    = player1->health;
}
