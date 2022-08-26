#include "GameAPI/Game.h"
#include "Player.h"

ObjectPlayer *Player;

void Player_SetOuttaHere(void)
{
    RSDK_THIS(Player);

    // Wait for ~3 minutes to do outta here
    if (self->outtaHereTimer >= 10620 && self->characterID == ID_SONIC) {
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_OUTTA_HERE, &self->animator, false, 0);
        self->state           = Player_State_OuttaHere;
        self->tileCollisions  = TILECOLLISION_NONE;
        self->interaction     = false;
        self->nextAirState    = StateMachine_None;
        self->nextGroundState = StateMachine_None;
        self->velocity.x      = 0;
        self->velocity.y      = 0;
        RSDK.PlaySfx(Player->sfxOuttahere, false, 255);
    }
}