#include "GameAPI/Game.h"
#include "ModConfig.h"

#include "BSS_Message.h"
#include "BSS_HUD.h"
#include "BSS_Setup.h"
#include "BSS_Collectable.h"

ModConfig config;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    // Setup Config
    config.alwaysGetRed = Mod.GetSettingsBool("", "Config:alwaysGetRed", false);
    Mod.SetSettingsBool("Config:alwaysGetRed", config.alwaysGetRed);
    Mod.SaveSettings();

    MOD_REGISTER_OBJ_OVERLOAD_MSV(BSS_Message, Mod_BSS_Message, NULL, NULL, NULL, NULL, NULL, BSS_Message_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(BSS_HUD, Mod_BSS_HUD, NULL, NULL, NULL, NULL, NULL, BSS_HUD_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(BSS_Setup, NULL, NULL, NULL, NULL, NULL, BSS_Setup_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(BSS_Collectable, NULL, NULL, NULL, NULL, BSS_Collectable_Create, NULL, NULL, NULL, NULL);
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
