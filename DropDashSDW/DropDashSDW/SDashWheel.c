#include "GameAPI/Game.h"
#include "SDashWheel.h"
#include "Player.h"

ObjectSDashWheel *SDashWheel;
ObjectPlayer *Player;

void SDashWheel_Update(void)
{
    RSDK_THIS(SDashWheel);

    bool32 dropDashOnWheel[PLAYER_COUNT] = { false };

    foreach_active(Player, player)
    {
        if (player->characterID == ID_SONIC && player->animator.animationID == ANI_DROPDASH) {
            int32 stoodPos = MIN(abs(self->position.x - player->position.x) >> 16, 31);

            Hitbox hitboxSolid;
            hitboxSolid.left   = -32;
            hitboxSolid.right  = 32;
            hitboxSolid.top    = SDashWheel->heightTable[stoodPos] - 36;
            hitboxSolid.bottom = -4 - hitboxSolid.top;
            if (Player_CheckCollisionBox(player, self, &hitboxSolid) == C_TOP) {
                player->animator.animationID                = ANI_SPINDASH;
                dropDashOnWheel[RSDK.GetEntitySlot(player)] = true;
            }
        }
    }

    Mod.Super(SDashWheel->classID, SUPER_UPDATE, NULL);
    
    foreach_active(Player, playerEnd)
    {
        if (dropDashOnWheel[RSDK.GetEntitySlot(player)])
            RSDK.SetSpriteAnimation(player->aniFrames, ANI_JUMP, &player->animator, false, 0);
    }
}
