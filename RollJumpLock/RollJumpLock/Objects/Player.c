#include "GameAPI/Game.h"
#include "Player.h"
#include "Shield.h"

ObjectPlayer *Player;

void Player_SetRollJumpLock(void)
{
    RSDK_THIS(Player);

    if (self->jumpAbilityState) {
        self->state        = Player_State_RollingAir;
        self->nextAirState = Player_State_RollingAir;
    }
}

void Player_State_RollingAir(void)
{
    RSDK_THIS(Player);

    self->left  = false;
    self->right = false;

    ObjectShield *Shield = Mod.FindObject("Shield");
    EntityShield *shield = RSDK_GET_ENTITY(Player->playerCount + RSDK.GetEntitySlot(self), Shield);
    bool32 abilityCheck  = self->jumpAbilityState == 1; // Check if the player has yet to use an ability

    Player_State_Air();

    if (((self->jumpAbilityState == 0 && abilityCheck) // If an ability besides the Drop Dash has been used (namely a Sonic shield ability)
        || (shield && shield->inkEffect == INK_ADD && shield->alpha == 0x100)) // If the Instashield has been used
        && self->state == Player_State_RollingAir)
        self->state = Player_State_Air;
    else if (self->state == Player_State_DropDash)
        self->state = Player_State_RollingDropDash;
}

void Player_State_RollingDropDash(void)
{
    RSDK_THIS(Player);

    self->left  = false;
    self->right = false;

    Player_State_DropDash();

    if (self->state == Player_State_Air)
        self->state = Player_State_RollingAir;
}