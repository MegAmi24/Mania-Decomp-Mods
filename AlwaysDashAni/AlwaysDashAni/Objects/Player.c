#include "Player.h"
#include "../ModVersion.h"
#if !MODVER_100
#include "../ModConfig.h"
#endif

ObjectPlayer *Player;

void Player_Create(void)
{
    RSDK_THIS(Player);

    printf("Hooked onto Player!\n");

    if (!SceneInfo->inEditor && self->characterID == ID_SONIC) {
        self->aniFrames = Player->sonicFrames;

        // Set Peelout animation to Dash
#if MODVER_100
        for (int32 f = 0; f < 4; ++f) {
            SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_PEELOUT, f);
            SpriteFrame *src = RSDK.GetFrame(self->aniFrames, ANI_DASH, f + 1);

            *dst = *src;
            printf("Setting Peelout Animation Frame!\n");
        }
#else
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
#endif
    }

#if MODVER_100
    Mod.Super(Player->classID, SUPER_CREATE, NULL);
#else
    Mod.Super(self->classID, SUPER_CREATE, NULL);
#endif
}