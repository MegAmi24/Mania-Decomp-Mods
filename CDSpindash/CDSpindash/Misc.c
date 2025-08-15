#include "GameAPI/Game.h"
#include "Player.h"

ObjectDashLift *DashLift;
ObjectSDashWheel *SDashWheel;

void SDashWheel_Update(void)
{
    RSDK_THIS(SDashWheel);

    foreach_active(Player, player) {
        if (Player_CheckCollisionTouch(player, self, &SDashWheel->hitboxWheel) && player->state == Player_State_CDSpindash)
            player->animator.animationID = ANI_SPINDASH;
    }

    Mod.Super(SDashWheel->classID, SUPER_UPDATE, NULL);
    
    foreach_active(Player, playerEnd)
    {
        if (playerEnd->state == Player_State_CDSpindash && playerEnd->animator.animationID == ANI_SPINDASH)
            playerEnd->animator.animationID = ANI_JUMP;
    }
}

bool32 DashLift_State_HandleDash_Hook(bool32 skipped)
{
    RSDK_THIS(DashLift);

    foreach_active(Player, player)
    {
        if (((1 << RSDK.GetEntitySlot(player)) & self->stoodPlayers)) {
            // Use the normal Spindash on Dash Lifts
            if (player->state == Player_State_CDSpindash) {
                RSDK.SetSpriteAnimation(player->aniFrames, ANI_SPINDASH, &player->animator, true, 0);
                player->state = Player_State_Spindash;
                player->position.y -= TO_FIXED(5);
                RSDK.StopSfx(Player->sfxPeelCharge);
                RSDK.PlaySfx(Player->sfxCharge, false, 255);
            }
        }
    }

    return false;
}
