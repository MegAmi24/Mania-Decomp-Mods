#include "GameAPI/Game.h"
#include "TitleSetup.h"
#include "TitleLogo.h"
#include "TitleEggman.h"
#include "ModConfig.h"

#if MANIA_USE_PLUS
void (*TitleSetup_CheckCheatCode)(void) = NULL;
#endif
StateMachine(TitleSetup_State_WaitForSonic) = NULL;
StateMachine(TitleSetup_State_SetupLogo) = NULL;
#if MANIA_USE_PLUS
StateMachine(TitleSetup_State_SetupPlusLogo) = NULL;
StateMachine(TitleSetup_State_WaitForEnter) = NULL;
#endif

ObjectTitleSetup *TitleSetup;

#if MANIA_USE_PLUS
bool32 TitleSetup_State_SetupPlusLogo_Hook(bool32 skipped)
{
    RSDK_THIS(TitleSetup);

    if (self->timer < 120)
        TitleSetup_CheckCheatCode();

    if (++self->timer == 120) {
        ObjectTitleLogo *TitleLogo = Mod.FindObject("TitleLogo");
        foreach_all(TitleLogo, titleLogo)
        {
            switch (titleLogo->type) {
                case TITLELOGO_RIBBON:
                case TITLELOGO_GAMETITLE:
                    titleLogo->storeY     = titleLogo->position.y - 0x70000;
                    titleLogo->velocity.y = -0x30000;
                    titleLogo->timer      = 2;
                    titleLogo->state      = TitleLogo_State_HandleSetup;

                    RSDK.PlaySfx(TitleLogo->sfxPlus, false, 255);
                    break;

                case TITLELOGO_PRESSSTART:
                    titleLogo->position.y += 0x80000;

                    if (config.earlyStart) {
                        titleLogo->active  = ACTIVE_NORMAL;
                        titleLogo->visible = true;

                        Entity *store     = SceneInfo->entity;
                        SceneInfo->entity = (Entity *)titleLogo;
                        TitleLogo_SetupPressStart();
                        SceneInfo->entity = store;
                    }
                    break;

                case TITLELOGO_PLUS:
                    titleLogo->active  = ACTIVE_NORMAL;
                    titleLogo->visible = true;
                    titleLogo->timer   = 2;
                    titleLogo->position.y -= 0x40000;
                    if (config.fixPlusPos)
                        titleLogo->storeY -= 0x10000;
                    titleLogo->state = TitleLogo_State_HandleSetup;
                    break;

                default: break;
            }
        }

        if (config.enableEggman) {
            ObjectTitleEggman *TitleEggman = Mod.FindObject("TitleEggman");
            CREATE_ENTITY(TitleEggman, NULL, 0, 0xC00000);
        }
        self->timer = config.earlyStart ? -120 : 0;
        self->state = config.earlyStart ? TitleSetup_State_WaitForEnter : TitleSetup_State_SetupLogo;
    }

    return true;
}
#endif
