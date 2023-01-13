#include "Player.h"
#include "ModConfig.h"

ObjectPlayer *Player;

void Player_Create(void)
{
    RSDK_THIS(Player);

    printf("Hooked onto Player!\n");

    if (!SceneInfo->inEditor && self->characterID == ID_SONIC) {
        self->aniFrames = Player->sonicFrames;

        // Set Peelout animation to Dash (or vice versa)
        if (config.PeeloutAnim) {
            for (int32 f = 0; f < 4; ++f) {
                SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_DASH, f + 1);
                SpriteFrame *src = RSDK.GetFrame(self->aniFrames, ANI_PEELOUT, f);

                *dst = *src;
                printf("Setting Dash Animation Frame!\n");
            }
        }
        else {
            for (int32 f = 0; f < 4; ++f) {
                SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_PEELOUT, f);
                SpriteFrame *src = RSDK.GetFrame(self->aniFrames, ANI_DASH, f + 1);

                *dst = *src;
                printf("Setting Peelout Animation Frame!\n");
            }
        }
    }

    Mod.Super(self->classID, SUPER_CREATE, NULL);
}