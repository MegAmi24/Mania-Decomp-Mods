#include "GameAPI/Game.h"
#include "Player.h"
#include "MegAmiMenu.h"

Hitbox *(*Player_GetAltHitbox)(EntityPlayer *player) = NULL;
void (*Player_GiveRings)(EntityPlayer *player, int32 amount, bool32 playSfx) = NULL;
void (*Player_ChangeCharacter)(EntityPlayer *player, int32 character) = NULL;
bool32 (*Player_TryTransform)(EntityPlayer *player, uint8 emeraldMasks) = NULL;
void (*Player_ApplyShield)(EntityPlayer *player) = NULL;
void (*Player_UpdatePhysicsState)(EntityPlayer *entity) = NULL;
StateMachine(Player_State_Death) = NULL;
StateMachine(Player_State_Drown) = NULL;

ObjectPlayer *Player;

void Player_Update(void)
{
    RSDK_THIS(Player);

    // Handle Invincibility Toggle
    if (MegAmiMenu->playerInv[self->playerID] && self->blinkTimer >= 0 && self->blinkTimer <= 2)
        self->blinkTimer = 2;

    Mod.Super(Player->classID, SUPER_UPDATE, NULL);
}

bool32 Player_Input_P1_Hook(bool32 skippedState)
{
    RSDK_THIS(Player);

#if MANIA_USE_PLUS
    if (self->stateInputReplay != StateMachine_None)
        return false;
#endif

    ObjectAnnouncer *Announcer = Mod.FindObject("Announcer");
    if (!Announcer)
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
        if (globals->gameMode != MODE_COMPETITION || Announcer->finishedCountdown) {
            ObjectLottoMachine *LottoMachine = Mod.FindObject("LottoMachine");
            if (!LottoMachine || !((1 << self->playerID) & LottoMachine->activePlayers)) {
                if (ControllerInfo[self->controllerID].keySelect.press) {
                    if (self->state != Player_State_Death && self->state != Player_State_Drown) {
                        CREATE_ENTITY(MegAmiMenu, self, self->position.x, self->position.y);
                        ControllerInfo[self->controllerID].keySelect.press = false;
                    }
                }
            }
        }
    }

    return false;
}
