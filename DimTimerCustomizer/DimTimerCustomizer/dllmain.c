#include "../GameAPI/C/GameAPI/Game.h"
#include "Objects/ReplayRecorder.h"
#include "ModConfig.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

ModConfig config;

void DimTimerCustomizerHook(void *data)
{
    UNUSED(data);
    
    ObjectReplayRecorder *recorder = Mod.FindObject("ReplayRecorder");
    EntityReplayRecorder *manager  = recorder->playbackManager;

    if (recorder && manager && manager->active == ACTIVE_NORMAL) // If a replay is playing
        RSDK.SetVideoSetting(VIDEOSETTING_DIMTIMER, config.TAttackDimTimer * RSDK.GetVideoSetting(VIDEOSETTING_REFRESHRATE));
    else
        RSDK.SetVideoSetting(VIDEOSETTING_DIMTIMER, config.NormalDimTimer * RSDK.GetVideoSetting(VIDEOSETTING_REFRESHRATE));

    if (!config.EnableDim)
        RSDK.SetVideoSetting(VIDEOSETTING_DIMTIMER, 9999999999);
}

void InitModAPI(void)
{
    // Register State Hooks
    Mod.AddModCallback(MODCB_ONLATEUPDATE, DimTimerCustomizerHook);

    // Setup Config
    config.EnableDim       = Mod.GetSettingsBool("", "Config:EnableDim", true);
    config.NormalDimTimer  = Mod.GetSettingsInteger("", "Config:NormalDimTimer", 300);
    config.TAttackDimTimer = Mod.GetSettingsInteger("", "Config:TAttackDimTimer", 900);

    Mod.SetSettingsBool("Config:EnableDim", config.EnableDim);
    Mod.SetSettingsInteger("Config:NormalDimTimer", config.NormalDimTimer);
    Mod.SetSettingsInteger("Config:TAttackDimTimer", config.TAttackDimTimer);
    Mod.SaveSettings();
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