#include "GameAPI/Game.h"
#include "Player.h"

ObjectPlayer *Player;

bool32 Player_State_TailsFlight_Hook(bool32 skipped)
{
    RSDK_THIS(Player);

    if (self->onGround)
        return false;

    if (self->timer < 480) {
        EntityPlayer *leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        if (!self->underwater || leader->state != Player_State_FlyCarried) {
            if (self->up) {
                self->abilitySpeed = -0x2000;
                self->abilityValue = 0;
            }
            else if (self->down) {
                if (self->velocity.y < 0)
                    self->velocity.y += 0x3000;
                self->abilitySpeed = 0x2000;
                self->abilityValue = 0;
                if (self->velocity.y > 0x60000)
                    self->velocity.y = 0x60000;
            }
        }
    }

    if ((!self->sidekick || self->stateInput == Player_Input_P2_Player) && self->jumpPress && self->down) {
        self->state = Player_State_Air;
        self->jumpAbilityState = 0;
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
    }

    return false;
}

bool32 Player_JumpAbility_Knux_Hook(bool32 skipped)
{
    RSDK_THIS(Player);

    if (self->jumpPress && self->jumpAbilityState == 1
        && (self->stateInput != Player_Input_P2_AI
            || (self->up
#if MANIA_USE_PLUS
                && globals->gameMode != MODE_ENCORE
#endif
                ))) {
        if (!self->invertGravity)
            self->velocity.y += 0x20000;
    }

    return false;
}

bool32 Player_State_KnuxGlideDrop_Hook(bool32 skipped)
{
    RSDK_THIS(Player);

    if (self->onGround && !self->groundVel && self->jumpPress) {
        Player_GroundActionControls();
        self->skidding = 0;
        self->timer    = 0;
    }

    return false;
}

bool32 Player_State_KnuxGlideSlide_Hook(bool32 skipped)
{
    RSDK_THIS(Player);

    ObjectZone *Zone = Mod.FindObject("Zone");
    if (self->onGround && self->jumpPress && (!self->groundVel || Zone->autoScrollSpeed)) {
        Player_GroundActionControls();
        self->skidding = 0;
    }

    return false;
}

void Player_GroundActionControls(void)
{
    RSDK_THIS(Player);

    if (self->jumpPress) {
        if (self->up) {
            if (self->statePeelout)
                StateMachine_Run(self->statePeelout);
            else
                Player_Action_Jump(self);
        }
        else if (self->down)
            Player_Action_Spindash();
        else
            Player_Action_Jump(self);
    }
}
