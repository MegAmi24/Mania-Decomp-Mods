#include "GameAPI/Game.h"
#include "Player.h"
#include "ModConfig.h"

ModConfig config;

// Resolve externals
int32 (*HUD_CharacterIndexFromID)(int32 characterID);

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    // Setup Config
    config.sonicCanOuttaHere = Mod.GetSettingsBool("", "Config:sonicCanOuttaHere", true);
    config.tailsCanOuttaHere = Mod.GetSettingsBool("", "Config:tailsCanOuttaHere", true);
    config.knuxCanOuttaHere  = Mod.GetSettingsBool("", "Config:knuxCanOuttaHere", true);
#if MANIA_USE_PLUS
    config.mightyCanOuttaHere = Mod.GetSettingsBool("", "Config:mightyCanOuttaHere", true);
    config.rayCanOuttaHere    = Mod.GetSettingsBool("", "Config:rayCanOuttaHere", true);
#endif
    config.sidekickCanOuttaHere = Mod.GetSettingsInteger("", "Config:sidekickCanOuttaHere", 0);
    config.sonicAnimID          = Mod.GetSettingsInteger("", "Config:sonicAnimID", -1);
    config.superSonicAnimID     = Mod.GetSettingsInteger("", "Config:superSonicAnimID", -1);
    config.tailsAnimID          = Mod.GetSettingsInteger("", "Config:tailsAnimID", -1);
    config.knuxAnimID           = Mod.GetSettingsInteger("", "Config:knuxAnimID", -1);
#if MANIA_USE_PLUS
    config.mightyAnimID = Mod.GetSettingsInteger("", "Config:mightyAnimID", -1);
    config.rayAnimID    = Mod.GetSettingsInteger("", "Config:rayAnimID", -1);
#endif
    config.sidekickAnimID = Mod.GetSettingsInteger("", "Config:sidekickAnimID", -1);
    config.useFrameID     = Mod.GetSettingsBool("", "Config:useFrameID", false);
    config.useVoiceLines  = Mod.GetSettingsInteger("", "Config:useVoiceLines", 2);

    Mod.SetSettingsBool("Config:sonicCanOuttaHere", config.sonicCanOuttaHere);
    Mod.SetSettingsBool("Config:tailsCanOuttaHere", config.tailsCanOuttaHere);
    Mod.SetSettingsBool("Config:knuxCanOuttaHere", config.knuxCanOuttaHere);
#if MANIA_USE_PLUS
    Mod.SetSettingsBool("Config:mightyCanOuttaHere", config.mightyCanOuttaHere);
    Mod.SetSettingsBool("Config:rayCanOuttaHere", config.rayCanOuttaHere);
#endif
    Mod.SetSettingsInteger("Config:sidekickCanOuttaHere", CLAMP(config.sidekickCanOuttaHere, 0, 2));
    Mod.SetSettingsInteger("Config:sonicAnimID", config.sonicAnimID);
    Mod.SetSettingsInteger("Config:superSonicAnimID", config.superSonicAnimID);
    Mod.SetSettingsInteger("Config:tailsAnimID", config.tailsAnimID);
    Mod.SetSettingsInteger("Config:knuxAnimID", config.knuxAnimID);
#if MANIA_USE_PLUS
    Mod.SetSettingsInteger("Config:mightyAnimID", config.mightyAnimID);
    Mod.SetSettingsInteger("Config:rayAnimID", config.rayAnimID);
#endif
    Mod.SetSettingsInteger("Config:sidekickAnimID", config.sidekickAnimID);
    Mod.SetSettingsBool("Config:useFrameID", config.useFrameID);
    Mod.SetSettingsInteger("Config:useVoiceLines", CLAMP(config.useVoiceLines, 0, 2));

    Mod.SaveSettings();

    HUD_CharacterIndexFromID = Mod.GetPublicFunction(NULL, "HUD_CharacterIndexFromID");

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