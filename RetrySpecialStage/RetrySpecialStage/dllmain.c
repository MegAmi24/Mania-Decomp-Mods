#include "GameAPI/Game.h"
#include "ModConfig.h"
#include "UFO_Setup.h"
#include "Misc.h"

ModConfig config;

SaveRAM *(*SaveGame_GetSaveRAM)(void) = NULL;
EntityUIDialog *(*UIDialog_CreateDialogYesNo)(String *text, void (*callbackYes)(void), void (*callbackNo)(void), bool32 closeOnSelect_Yes,
                                              bool32 closeOnSelect_No) = NULL;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    // Setup Config
    config.costLives = Mod.GetSettingsBool("", "Config:costLives", true);
    Mod.SetSettingsBool("Config:costLives", config.costLives);
    Mod.SaveSettings();

    UFO_Setup_State_FinishFadeout = Mod.GetPublicFunction(NULL, "UFO_Setup_State_FinishFadeout");
    SaveGame_GetSaveRAM           = Mod.GetPublicFunction(NULL, "SaveGame_GetSaveRAM");
    UIDialog_CreateDialogYesNo    = Mod.GetPublicFunction(NULL, "UIDialog_CreateDialogYesNo");

    // Register State Hooks
    Mod.RegisterStateHook(UFO_Setup_State_FinishFadeout, UFO_Setup_State_FinishFadeout_Hook, true);

    MOD_REGISTER_OBJECT_HOOK(UFO_Setup);
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
