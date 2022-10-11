#include "../GameAPI/C/GameAPI/Game.h"
#include "ModVersion.h"
#if MOD_VERSION != MODVER_100
#include "ModConfig.h"
#endif

#include "Objects/Player.h"
#include "Objects/Camera.h"

#if MOD_VERSION != MODVER_100
ModConfig config;
#endif

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
#if MOD_VERSION != MODVER_100
    // Setup Config
    config.PeeloutAnim = Mod.GetSettingsBool("", "Config:PeeloutAnim", false);
    Mod.SetSettingsBool("Config:PeeloutAnim", config.PeeloutAnim);
    Mod.SaveSettings();
#endif

    MOD_REGISTER_OBJ_OVERLOAD(Player, NULL, NULL, NULL, NULL, Player_Create, NULL, NULL, NULL, NULL);

    printf("Hello From Always Dash Ani Initialization!\n");
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif