#include "GameAPI/Game.h"
#include "Player.h"
#include "../ModConfig.h"
#include "Zone.h"

ObjectPlayer *Player;
ModObjectPlayer *Mod_Player;

void Player_Update(void)
{
    RSDK_THIS(Player);

    int32 deathCheck = self->deathType;

    Mod.Super(Player->classID, SUPER_UPDATE, NULL);

    self->crushDeath = (self->deathType != deathCheck && !self->sidekick);

    //Mod.Super(Player->classID, SUPER_CREATE, NULL);
}

void Player_LateUpdate(void)
{
    RSDK_THIS(Player);

    if (!self->sidekick) {
        // Handle getting hit
        if (self->state != Player_State_Hurt)
            self->storeRings = self->rings;
        else {
            if (self->rings == 0 && self->storeRings != 0) {
                self->rings = self->storeRings;
                RSDK.StopSfx(Player->sfxLoseRings);
                RSDK.PlaySfx(Player->sfxHurt, false, 255);

                if (--self->health <= 0) {
                    self->deathType = PLAYER_DEATH_DIE_USESFX;
                }
            }
        }

        // Handle death
        if (self->deathType && self->health > 0 && !self->crushDeath) {
            if (--self->health > 0) {
                self->deathType = PLAYER_DEATH_NONE;
                self->state     = Player_State_Hurt;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_HURT, &self->animator, false, 0);
                self->velocity.y     = -0x40000;
                self->onGround       = false;
                self->tileCollisions = TILECOLLISION_DOWN;
                self->blinkTimer     = 120;
                if (self->underwater) {
                    self->velocity.x >>= 1;
                    self->velocity.y = -0x20000;
                }
                RSDK.PlaySfx(Player->sfxHurt, false, 255);
            }
        }

        // Pits should still kill you
        ObjectZone *Zone = Mod.FindObject("Zone");
        int32 playerID   = RSDK.GetEntitySlot(self);

        if (self->state != Player_State_Death && self->position.y > Zone->deathBoundary[playerID]) {
            self->deathType = PLAYER_DEATH_DIE_USESFX;
        }
    }

    Mod.Super(Player->classID, SUPER_LATEUPDATE, NULL);
}

void Player_Create(void *data)
{
    RSDK_THIS(Player);

    Mod.Super(self->classID, SUPER_CREATE, NULL);

    if (!SceneInfo->inEditor) {
        self->health       = Mod_Player->health;
        if (self->health == 0)
            self->health = config.StartingHealth;
        Mod_Player->health = config.StartingHealth;
    }
}