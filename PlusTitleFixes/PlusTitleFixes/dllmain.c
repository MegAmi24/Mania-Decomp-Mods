#include "../GameAPI/C/GameAPI/Game.h"
#include "Objects/TitleSetup.h"
#include "Objects/TitleLogo.h"
#include "ModConfig.h"

ModConfig config;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    // Setup Config
    config.earlyStart   = Mod.GetSettingsBool("", "Config:earlyStart", true);
    config.fixPlusPos   = Mod.GetSettingsBool("", "Config:fixPlusPos", true);
    config.enableEggman = Mod.GetSettingsBool("", "Config:enableEggman", true);

    Mod.SetSettingsBool("Config:earlyStart", config.earlyStart);
    Mod.SetSettingsBool("Config:fixPlusPos", config.fixPlusPos);
    Mod.SetSettingsBool("Config:enableEggman", config.enableEggman);

    Mod.SaveSettings();

    TitleSetup_CheckCheatCode      = Mod.GetPublicFunction(NULL, "TitleSetup_CheckCheatCode");
    TitleSetup_State_WaitForSonic  = Mod.GetPublicFunction(NULL, "TitleSetup_State_WaitForSonic");
    TitleSetup_State_SetupLogo     = Mod.GetPublicFunction(NULL, "TitleSetup_State_SetupLogo");
#if MANIA_USE_PLUS
    TitleSetup_State_SetupPlusLogo = Mod.GetPublicFunction(NULL, "TitleSetup_State_SetupPlusLogo");
#endif
    TitleSetup_State_WaitForEnter  = Mod.GetPublicFunction(NULL, "TitleSetup_State_WaitForEnter");
    TitleLogo_SetupPressStart      = Mod.GetPublicFunction(NULL, "TitleLogo_SetupPressStart");
    TitleLogo_State_HandleSetup    = Mod.GetPublicFunction(NULL, "TitleLogo_State_HandleSetup");

#if MANIA_USE_PLUS
    Mod.RegisterStateHook(TitleSetup_State_SetupPlusLogo, TitleSetup_State_SetupPlusLogo_Hook, true);
#endif

    MOD_REGISTER_OBJECT_HOOK(TitleSetup);
}

#if RETRO_USE_MOD_LOADER
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