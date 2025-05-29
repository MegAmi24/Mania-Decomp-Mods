#include "GameAPI/Game.h"
#include "HUD.h"
#include "Player.h"

ObjectHUD *HUD;

void HUD_LateUpdate()
{
    RSDK_THIS(HUD);

    EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

    int32 ringStore = player->rings;
    player->rings   = 0;
    Mod.Super(HUD->classID, SUPER_LATEUPDATE, NULL);
    player->rings = ringStore;
}
