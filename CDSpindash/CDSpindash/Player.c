#include "GameAPI/Game.h"
#include "Player.h"

bool32 (*Player_CheckCollisionTouch)(EntityPlayer *player, void *e, Hitbox *entityHitbox) = NULL;
StateMachine(Player_State_Ground) = NULL;
StateMachine(Player_State_Roll) = NULL;
StateMachine(Player_State_Spindash) = NULL;
StateMachine(Camera_State_FollowY) = NULL;

ObjectPlayer *Player;

void Player_LateUpdate(void)
{
    RSDK_THIS(Player);

    Mod.Super(Player->classID, SUPER_LATEUPDATE, NULL);

    if (self->tailFrames != (uint16)-1 && self->state == Player_State_CDSpindash)
        self->tailDirection = self->direction;
}

void Player_Action_CDSpindash(void)
{
    RSDK_THIS(Player);

    if (self->state == Player_State_Spindash) {
        self->state = Player_State_CDSpindash;

        ObjectDust *Dust = Mod.FindObject("Dust");
        foreach_active(Dust, dust)
        {
            if (dust->parent == (Entity *)self)
                destroyEntity(dust);
        }

        RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, true, 0);
        self->position.y += TO_FIXED(5);
        self->animator.speed = self->characterID == ID_TAILS ? 120 : 0xF0;

        RSDK.StopSfx(Player->sfxCharge);
        RSDK.PlaySfx(Player->sfxPeelCharge, false, 255);
    }
}

void Player_State_CDSpindash(void)
{
    RSDK_THIS(Player);

    if (self->gravityStrength == 0x1000) {
        if (self->superState == SUPERSTATE_SUPER) {
            self->abilityTimer += 0xA000;
            if (self->abilityTimer > 0xA0000)
                self->abilityTimer = 0xA0000;
        }
        else {
            self->abilityTimer += 0x6000;
            if (self->abilityTimer > 0x80000)
                self->abilityTimer = 0x80000;
        }
    }
    else if (self->superState == SUPERSTATE_SUPER) {
        self->abilityTimer += 0xC000;
        if (self->abilityTimer > 0xD0000)
            self->abilityTimer = 0xD0000;
    }
    else {
        self->abilityTimer += 0x8000;
        if (self->abilityTimer > 0xC0000)
            self->abilityTimer = 0xC0000;
    }

    if (!self->down) {
        RSDK.StopSfx(Player->sfxPeelCharge);

        if (self->abilityTimer < 0x40000) {
            self->groundVel = 0;
            self->state     = Player_State_Ground;
        }
        else {
            ObjectZone *Zone = Mod.FindObject("Zone");
            if (self->camera && !Zone->autoScrollSpeed) {
                self->scrollDelay   = 15;
                self->camera->state = Camera_State_FollowY;
            }

            self->state = Player_State_Roll;
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, true, 0);
            if (self->direction)
                self->groundVel = -self->abilityTimer;
            else
                self->groundVel = self->abilityTimer;

            RSDK.PlaySfx(Player->sfxPeelRelease, false, 0xFF);
        }
    }
}
