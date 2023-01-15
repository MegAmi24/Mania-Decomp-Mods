#include "Player.h"
#include "ModConfig.h"

ObjectPlayer *Player;

void Player_StageLoad(void)
{
    RSDK_THIS(Player);

    Mod.Super(Player->classID, SUPER_STAGELOAD, NULL);

    if (!Player->sonicFrames)
        Player->sonicFrames = RSDK.LoadSpriteAnimation("Players/Sonic.bin", SCOPE_STAGE);

    // Set Peelout animation to Dash (or vice versa)
    if (config.PeeloutAnim) {
        for (int32 f = 0; f < 4; ++f) {
            SpriteFrame *dst = RSDK.GetFrame(Player->sonicFrames, ANI_DASH, f + 1);
            SpriteFrame *src = RSDK.GetFrame(Player->sonicFrames, ANI_PEELOUT, f);

            *dst = *src;
        }
    }
    else {
        for (int32 f = 0; f < 4; ++f) {
            SpriteFrame *dst = RSDK.GetFrame(Player->sonicFrames, ANI_PEELOUT, f);
            SpriteFrame *src = RSDK.GetFrame(Player->sonicFrames, ANI_DASH, f + 1);

            *dst = *src;
        }
    }
}