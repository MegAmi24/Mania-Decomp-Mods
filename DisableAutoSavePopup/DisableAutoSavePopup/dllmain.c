#include "GameAPI/Game.h"
#include "ModConfig.h"
#include "UIUsernamePopup.h"
#include "UIWaitSpinner.h"

ObjectUIUsernamePopup *UIUsernamePopup;
ObjectUIWaitSpinner *UIWaitSpinner;

ModConfig config;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void DisableAutoSavePopupHook(void *data)
{
    UNUSED(data);

    if (!config.showAutosaveIcon || !config.showAutosavePopup)
        globals->notifiedAutosave = true;
}

void UIUsernamePopup_Draw(void)
{
    RSDK_THIS(UIUsernamePopup);

    if (config.showUsernamePopup)
        Mod.Super(UIUsernamePopup->classID, SUPER_DRAW, NULL);
}

void UIWaitSpinner_Draw(void)
{
    RSDK_THIS(UIWaitSpinner);

    if (config.showAutosaveIcon)
        Mod.Super(UIWaitSpinner->classID, SUPER_DRAW, NULL);
}

void InitModAPI(void)
{
    // Setup Config
    config.showAutosavePopup = Mod.GetSettingsBool("", "Config:showAutosavePopup", true);
    config.showUsernamePopup = Mod.GetSettingsBool("", "Config:showUsernamePopup", true);
    config.showAutosaveIcon  = Mod.GetSettingsBool("", "Config:showAutosaveIcon", true);

    Mod.SetSettingsBool("Config:showAutosaveIcon", config.showAutosaveIcon);
    Mod.SetSettingsBool("Config:showUsernamePopup", config.showUsernamePopup);
    Mod.SetSettingsBool("Config:showAutosavePopup", config.showAutosavePopup);

    Mod.SaveSettings();

    Mod.AddModCallback(MODCB_ONSTAGELOAD, DisableAutoSavePopupHook);

    MOD_REGISTER_OBJ_OVERLOAD(UIUsernamePopup, NULL, NULL, NULL, UIUsernamePopup_Draw, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(UIWaitSpinner, NULL, NULL, NULL, UIWaitSpinner_Draw, NULL, NULL, NULL, NULL, NULL);
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
