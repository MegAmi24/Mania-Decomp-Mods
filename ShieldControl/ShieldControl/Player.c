#include "GameAPI/Game.h"
#include "Player.h"
#include "Misc.h"

void (*Player_ApplyShield)(EntityPlayer *player) = NULL;
StateMachine(Player_State_Air) = NULL;
StateMachine(Player_State_BubbleBounce) = NULL;
StateMachine(Player_JumpAbility_Sonic) = NULL;

ObjectPlayer *Player;

void Player_Update()
{
    RSDK_THIS(Player);

    if (self->stateAbility == Player_JumpAbility_Sonic)
        self->stateAbility = Player_JumpAbility_SonicShieldControl;

    if (self->state == Player_State_BubbleBounce)
        self->state = Player_State_NoShieldBounce;

    Mod.Super(Player->classID, SUPER_UPDATE, NULL);
}

void Player_JumpAbility_SonicShieldControl()
{
    RSDK_THIS(Player);

    if (self->jumpAbilityState == 1 && self->jumpPress) {
        int8 shieldStore      = self->shield;
        int32 invincibleStore = self->invincibleTimer;

        ObjectShield *Shield                   = Mod.FindObject("Shield");
        ObjectInvincibleStars *InvincibleStars = Mod.FindObject("InvincibleStars");
        EntityShield *shield                   = RSDK_GET_ENTITY(Player->playerCount + RSDK.GetEntitySlot(self), Shield);
        Animator storeAnimator                 = shield->shieldAnimator;
        Animator storefxAnimator               = shield->fxAnimator;

        self->invincibleTimer = 0;

        if (self->superState == SUPERSTATE_SUPER || (shield && shield->classID == InvincibleStars->classID))
            self->shield = SHIELD_BLUE;

        if (self->up)
            self->shield = SHIELD_LIGHTNING;
        else if (self->left || self->right)
            self->shield = SHIELD_FIRE;
        else if (self->down)
            self->shield = SHIELD_BUBBLE;

        StateMachine_Run(Player_JumpAbility_Sonic);

        self->invincibleTimer = invincibleStore;
        if (shieldStore != self->shield) {
            self->shield = shieldStore;
            Player_ApplyShield(self);
            if (shield && shield->classID == Shield->classID) {
                shield->shieldAnimator = storeAnimator;
                shield->fxAnimator     = storefxAnimator;
            }
        }

        if (self->state == Player_State_BubbleBounce)
            self->state = Player_State_NoShieldBounce;
    }
    else
        StateMachine_Run(Player_JumpAbility_Sonic);
}

void Player_State_NoShieldBounce()
{
    RSDK_THIS(Player);

    int8 shieldStore      = self->shield;
    int32 invincibleStore = self->invincibleTimer;
    int32 superStore      = self->superState;

    ObjectShield *Shield     = Mod.FindObject("Shield");
    EntityShield *shield     = RSDK_GET_ENTITY(Player->playerCount + RSDK.GetEntitySlot(self), Shield);
    Animator storeAnimator   = shield->shieldAnimator;
    Animator storefxAnimator = shield->fxAnimator;

    self->shield          = SHIELD_BUBBLE;
    self->invincibleTimer = 0;
    self->superState      = SUPERSTATE_NONE;

    StateMachine_Run(Player_State_BubbleBounce);

    self->invincibleTimer = invincibleStore;
    self->superState      = superStore;
    if (self->state == Player_State_Air && shieldStore != self->shield) {
        self->shield = shieldStore;
        Player_ApplyShield(self);
        if (shield && shield->classID == Shield->classID) {
            shield->shieldAnimator = storeAnimator;
            shield->fxAnimator     = storefxAnimator;
        }
    }
    else
        self->shield = shieldStore;
}