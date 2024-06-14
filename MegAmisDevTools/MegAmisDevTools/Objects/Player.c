#include "GameAPI/Game.h"
#include "Player.h"
#include "MegAmiMenu.h"

ObjectPlayer *Player;

void Player_Update(void)
{
    RSDK_THIS(Player);

    // Handle Invincibility Toggle
    if (MegAmiMenu->playerInv[self->playerID] && self->blinkTimer >= 0 && self->blinkTimer <= 2)
        self->blinkTimer = 2;

    // Fix a possible crash when changing sidekick
    if (self->outerbox && !self->innerbox)
        self->innerbox = Player_GetAltHitbox(self);

    Mod.Super(Player->classID, SUPER_UPDATE, NULL);
}

bool32 Player_Input_P1_Hook(bool32 skippedState)
{
    RSDK_THIS(Player);

    ObjectAnnouncer *announcer = Mod.FindObject("Announcer");
    if (!announcer)
        return false;

    for (int32 t = 0; t < TouchInfo->count; ++t) {
        if (TouchInfo->down[t]) {
            int32 tx = (int32)(TouchInfo->x[t] * ScreenInfo->size.x);
            int32 ty = (int32)(TouchInfo->y[t] * ScreenInfo->size.y);

            if (tx <= 32 && ty >= (ScreenInfo->size.y - 32))
                ControllerInfo[self->controllerID].keySelect.press = true;
        }
    }

    if (self->controllerID <= CONT_P4) {
        if (globals->gameMode != MODE_COMPETITION || announcer->finishedCountdown) {
            ObjectLottoMachine *lottoMachine = Mod.FindObject("LottoMachine");
            if (!lottoMachine || !((1 << self->playerID) & lottoMachine->activePlayers)) {
                if (ControllerInfo[self->controllerID].keySelect.press) {
                    if (self->state != Mod.GetPublicFunction(NULL, "Player_State_Death")
                        && self->state != Mod.GetPublicFunction(NULL, "Player_State_Drown")) {
                        CREATE_ENTITY(MegAmiMenu, self, self->position.x, self->position.y);
                        ControllerInfo[self->controllerID].keySelect.press = false;
                    }
                }
            }
        }
    }

    return false;
}