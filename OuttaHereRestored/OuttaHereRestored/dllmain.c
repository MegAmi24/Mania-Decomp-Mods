#include "../GameAPI/C/GameAPI/Game.h"
#include "ModVersion.h"
#include "Objects/Player.h"
#if MOD_VERSION != MODVER_100
#include "ModConfig.h"

ModConfig config;
#endif

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
#if MOD_VERSION != MODVER_100
    // Setup Config
    config.superSonicOuttaHere = Mod.GetSettingsBool("", "Config:superSonicOuttaHere", true);
    config.tailsOuttaHere      = Mod.GetSettingsBool("", "Config:tailsOuttaHere", true);
    config.knuxOuttaHere       = Mod.GetSettingsBool("", "Config:knuxOuttaHere", true);
    config.mightyOuttaHere     = Mod.GetSettingsBool("", "Config:mightyOuttaHere", true);
    config.rayOuttaHere        = Mod.GetSettingsBool("", "Config:rayOuttaHere", true);
    config.uniqueCharSfx       = Mod.GetSettingsBool("", "Config:uniqueCharSfx", true);

    Mod.SetSettingsBool("Config:superSonicOuttaHere", config.superSonicOuttaHere);
    Mod.SetSettingsBool("Config:tailsOuttaHere", config.tailsOuttaHere);
    Mod.SetSettingsBool("Config:knuxOuttaHere", config.knuxOuttaHere);
    Mod.SetSettingsBool("Config:mightyOuttaHere", config.mightyOuttaHere);
    Mod.SetSettingsBool("Config:rayOuttaHere", config.rayOuttaHere);
    Mod.SetSettingsBool("Config:uniqueCharSfx", config.uniqueCharSfx);

    Mod.SaveSettings();

    // Handle Animations
    if (!config.superSonicOuttaHere)
        Mod.ExcludeFile("", "Data/Sprites/Players/SuperSonic.bin");
    if (!config.tailsOuttaHere)
        Mod.ExcludeFile("", "Data/Sprites/Players/Tails.bin");
    if (!config.knuxOuttaHere)
        Mod.ExcludeFile("", "Data/Sprites/Players/Knux.bin");
    if (!config.mightyOuttaHere)
        Mod.ExcludeFile("", "Data/Sprites/Players/Mighty.bin");
    if (!config.rayOuttaHere)
        Mod.ExcludeFile("", "Data/Sprites/Players/Ray.bin");
#endif

    Player_State_OuttaHere = Mod.GetPublicFunction(NULL, "Player_State_OuttaHere");
#if MOD_VERSION != MODVER_100
    Player_HandleAirMovement = Mod.GetPublicFunction(NULL, "Player_HandleAirMovement");
#endif

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_Ground"), Player_SetOuttaHere, false);
#if MOD_VERSION != MODVER_100
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_OuttaHere"), Player_State_OuttaHere_Hook, true);
#endif
    MOD_REGISTER_OBJECT_HOOK(Player);
#if MOD_VERSION != MODVER_100
    MOD_REGISTER_OBJ_OVERLOAD_MSV(Player, Mod_Player, NULL, NULL, NULL, NULL, NULL, Player_StageLoad, NULL, NULL, NULL);
#endif
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