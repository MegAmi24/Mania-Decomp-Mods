#include "Player.h"
#include "ModVersion.h"
#if MOD_VERSION != MODVER_100
#include "ModConfig.h"
#endif

ObjectPlayer *Player;

void Player_Create(void)
{
    RSDK_THIS(Player);

    printf("Hooked onto Player!\n");

    if (!SceneInfo->inEditor && self->characterID == ID_SONIC) {
        self->aniFrames = Player->sonicFrames;

        // Set Peelout animation to Dash (or vice versa)
#if MOD_VERSION != MODVER_100
        if (config.PeeloutAnim) {
            for (int32 f = 0; f < 4; ++f) {
                SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_DASH, f + 1);
                SpriteFrame *src = RSDK.GetFrame(self->aniFrames, ANI_PEELOUT, f);

                *dst = *src;
                printf("Setting Dash Animation Frame!\n");
            }
        }
        else {
#endif
            for (int32 f = 0; f < 4; ++f) {
                SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_PEELOUT, f);
                SpriteFrame *src = RSDK.GetFrame(self->aniFrames, ANI_DASH, f + 1);

                *dst = *src;
                printf("Setting Peelout Animation Frame!\n");
            }
#if MOD_VERSION != MODVER_100
        }
#endif
    }

#if MOD_VERSION == MODVER_100
    Mod.Super(Player->classID, SUPER_CREATE, NULL);
#else
    Mod.Super(self->classID, SUPER_CREATE, NULL);
#endif
}