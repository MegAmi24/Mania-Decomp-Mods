#include "GameAPI/Game.h"

#if GAME_VERSION != VER_100 // Can't trick a hud element that doesn't exist
#include "HUD.h"
#include "Player.h"

ObjectHUD *HUD;

void HUD_LateUpdate()
{
    RSDK_THIS(HUD);

    ObjectERZSetup *ERZSetup = Mod.FindObject("ERZSetup");
    EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

    if ((player->state == Player_State_Transform || player->superState == SUPERSTATE_SUPER) && !ERZSetup) {
        SaveRAM *saveRAM   = SaveGame_GetSaveRAM();
        int32 ringStore    = player->rings;
        int32 superStore   = player->superState;
        int32 emeraldStore = saveRAM->collectedEmeralds;

        player->rings              = 50;
        player->superState         = SUPERSTATE_FADEIN;
        saveRAM->collectedEmeralds = 0b01111111;

        Mod.Super(HUD->classID, SUPER_LATEUPDATE, NULL);

        player->rings              = ringStore;
        player->superState         = superStore;
        saveRAM->collectedEmeralds = emeraldStore;
    }
    else
        Mod.Super(HUD->classID, SUPER_LATEUPDATE, NULL);
}
#endif