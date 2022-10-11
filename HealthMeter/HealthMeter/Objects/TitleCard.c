#include "GameAPI/Game.h"
#include "TitleCard.h"
#include "Zone.h"
#include "Player.h"
#include "../ModConfig.h"

ObjectTitleCard *TitleCard;

void Zone_TitleCard_SupressCB_Hook(void) { Mod_Player->health = config.StartingHealth; }