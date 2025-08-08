#include "GameAPI/Game.h"
#include "Player.h"

void (*Player_Action_Jump)(EntityPlayer *entity) = NULL;
StateMachine(Player_Action_Spindash) = NULL;
StateMachine(Player_State_Air) = NULL;
StateMachine(Player_State_FlyCarried) = NULL;
StateMachine(Player_Input_P2_AI) = NULL;
StateMachine(Player_Input_P2_Player) = NULL;

bool32 superCancel = false;

ObjectPlayer *Player;

bool32 Player_JumpAbility_Sonic_Hook(bool32 skipped)
{
    RSDK_THIS(Player);

    ObjectShield *Shield = Mod.FindObject("Shield");
    EntityShield *shield = RSDK_GET_ENTITY(Player->playerCount + RSDK.GetEntitySlot(self), Shield);
    if (self->invincibleTimer) {
        if (shield->classID != Shield->classID || shield->shieldAnimator.animationID != SHIELDANI_INSTA) {
            if (!(globals->medalMods & MEDAL_NODROPDASH))
                return false;
        }
    }

    if (self->shield == SHIELD_BUBBLE || self->shield == SHIELD_FIRE) {
        if (self->jumpAbilityState == 1) {
            if (self->up && (!self->sidekick || self->stateInput == Player_Input_P2_Player)) {
#if GAME_VERSION != VER_100
                if (!(Player_CanTransform() && ControllerInfo[self->controllerID].keyY.press)) {
#else
                if (!Player_CanTransform()) {
#endif
                    return true;
                }
            }
        }
    }  

    return false;
}

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

bool32 Player_State_KnuxGlideDrop_Hook(bool32 skipped)
{
    RSDK_THIS(Player);

    if (self->onGround && !self->groundVel && self->jumpPress) {
        self->skidding = 0;
        self->timer    = 0;
        Player_GroundActionControls();
    }

    return false;
}

bool32 Player_State_KnuxGlideSlide_Hook(bool32 skipped)
{
    RSDK_THIS(Player);

    ObjectZone *Zone = Mod.FindObject("Zone");
    if (self->onGround && self->jumpPress && (!self->groundVel || Zone->autoScrollSpeed)) {
        self->skidding = 0;
        Player_GroundActionControls();
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

// Function yoinked from ManiaTouchControls LOL
bool32 Player_CanTransform(void)
{
    RSDK_THIS(Player);

    if (!SceneInfo->timeEnabled)
        return false;

    if (superCancel && !RSDK.FindObject("ERZSetup") && self->superState == SUPERSTATE_SUPER)
        return true;

    SaveRAM *saveRAM = SaveGame_GetSaveRAM();
    if (!saveRAM)
        return false;

#if MANIA_USE_PLUS
    if (Player->canSuperCB && !Player->canSuperCB(false))
        return false;
#endif

    if (self->superState >= SUPERSTATE_SUPER || saveRAM->chaosEmeralds != 0x7F || self->rings < 50 || self->sidekick)
        return false;

    return true;
}
