#include "GameAPI/Game.h"
#include "Player.h"

ObjectPlayer *Player;

void Player_LateUpdate(void)
{
    RSDK_THIS(Player);

    if (self->animator.animationID == ANI_BORED_2 && self->animator.frameID == 2 && self->characterID == ID_SONIC)
        self->deathType = PLAYER_DEATH_DIE_USESFX;
    
    Mod.Super(Player->classID, SUPER_LATEUPDATE, NULL);
}