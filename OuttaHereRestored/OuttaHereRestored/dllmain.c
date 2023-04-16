#include "../GameAPI/C/GameAPI/Game.h"
#include "Player.h"
#include "ModConfig.h"

ModConfig config;

// Resolve externals
StateMachine(Player_State_OuttaHere);
StateMachine(Player_HandleAirMovement);

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    // Setup Config
    config.superSonicOuttaHere = Mod.GetSettingsBool("", "Config:superSonicOuttaHere", true);
    config.tailsOuttaHere      = Mod.GetSettingsBool("", "Config:tailsOuttaHere", true);
    config.knuxOuttaHere       = Mod.GetSettingsBool("", "Config:knuxOuttaHere", true);
#if MANIA_USE_PLUS
    config.mightyOuttaHere     = Mod.GetSettingsBool("", "Config:mightyOuttaHere", true);
    config.rayOuttaHere        = Mod.GetSettingsBool("", "Config:rayOuttaHere", true);
#endif
    config.uniqueCharSfx       = Mod.GetSettingsBool("", "Config:uniqueCharSfx", true);

    Mod.SetSettingsBool("Config:superSonicOuttaHere", config.superSonicOuttaHere);
    Mod.SetSettingsBool("Config:tailsOuttaHere", config.tailsOuttaHere);
    Mod.SetSettingsBool("Config:knuxOuttaHere", config.knuxOuttaHere);
#if MANIA_USE_PLUS
    Mod.SetSettingsBool("Config:mightyOuttaHere", config.mightyOuttaHere);
    Mod.SetSettingsBool("Config:rayOuttaHere", config.rayOuttaHere);
#endif
    Mod.SetSettingsBool("Config:uniqueCharSfx", config.uniqueCharSfx);

    Mod.SaveSettings();

    // Handle Animations
    if (!config.superSonicOuttaHere)
        Mod.ExcludeFile("", "Data/Sprites/Players/SuperSonic.bin");
    if (!config.tailsOuttaHere)
        Mod.ExcludeFile("", "Data/Sprites/Players/Tails.bin");
    if (!config.knuxOuttaHere)
        Mod.ExcludeFile("", "Data/Sprites/Players/Knux.bin");
#if MANIA_USE_PLUS
    if (!config.mightyOuttaHere)
        Mod.ExcludeFile("", "Data/Sprites/Players/Mighty.bin");
    if (!config.rayOuttaHere)
        Mod.ExcludeFile("", "Data/Sprites/Players/Ray.bin");
#endif

    Player_State_OuttaHere = Mod.GetPublicFunction(NULL, "Player_State_OuttaHere");
    Player_HandleAirMovement = Mod.GetPublicFunction(NULL, "Player_HandleAirMovement");

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_Ground"), Player_SetOuttaHere, false);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_OuttaHere"), Player_State_OuttaHere_Hook, true);
    MOD_REGISTER_OBJECT_HOOK(Player);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(Player, Mod_Player, NULL, NULL, NULL, NULL, NULL, Player_StageLoad, NULL, NULL, NULL);
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