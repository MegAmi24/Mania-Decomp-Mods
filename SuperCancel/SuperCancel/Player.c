#include "GameAPI/Game.h"
#include "Player.h"

ObjectPlayer *Player;

bool32 Player_SuperCancel(bool32 skipped)
{
    RSDK_THIS(Player);

    ObjectERZSetup *ERZSetup = Mod.FindObject("ERZSetup");

    if (ERZSetup)
        return false;

    if (self->animator.animationID == ANI_JUMP && self->velocity.y >= self->jumpCap && self->superState == SUPERSTATE_SUPER) {
        if (self->jumpAbilityState == 1) {
#if MANIA_USE_PLUS
            if (self->stateInput != Player_Input_P2_AI || (self->up && globals->gameMode != MODE_ENCORE)) {
#else
            if (self->stateInput != Player_Input_P2_AI || (self->up && self->characterID != ID_SONIC)) {
#endif
                if (ControllerInfo[self->controllerID].keyY.press) { // Just do this regardless of if it's 1.00 or not idc
                    self->superState = SUPERSTATE_FADEOUT;
                    self->jumpAbilityState = 0;
                }
            }
        }
    }

    return false;
}