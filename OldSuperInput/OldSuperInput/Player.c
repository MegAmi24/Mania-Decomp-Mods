#include "GameAPI/Game.h"
#include "Player.h"

ObjectPlayer *Player;

bool32 Player_OldSuperInput(bool32 skipped)
{
    RSDK_THIS(Player);

    ObjectERZSetup *ERZSetup = Mod.FindObject("ERZSetup");

    if (ERZSetup)
        return false;

    if (self->animator.animationID == ANI_JUMP && self->velocity.y >= self->jumpCap) {
        if (self->jumpAbilityState == 1) {
#if MANIA_USE_PLUS
            if (self->stateInput != Player_Input_P2_AI || (self->up && globals->gameMode != MODE_ENCORE)) {
#else
            if (self->stateInput != Player_Input_P2_AI || (self->up && self->characterID != ID_SONIC)) {
#endif
                if (self->jumpPress)
                    return Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds);
            }
        }
    }

    return false;
}
