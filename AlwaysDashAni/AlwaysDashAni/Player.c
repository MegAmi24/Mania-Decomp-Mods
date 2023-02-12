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
    for (int32 f = 0; f < 4; ++f) {
        SpriteFrame *dash = RSDK.GetFrame(Player->sonicFrames, ANI_DASH, f + 1);
        SpriteFrame *peelout = RSDK.GetFrame(Player->sonicFrames, ANI_PEELOUT, f);

        if (config.PeeloutAnim)
            *dash = *peelout;
        else
            *peelout = *dash;
    }
}