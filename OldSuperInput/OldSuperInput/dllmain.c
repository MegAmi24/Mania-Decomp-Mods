#include "GameAPI/Game.h"
#include "Player.h"
#include "HUD.h"

SaveRAM *(*SaveGame_GetSaveRAM)(void) = NULL;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    // Get Public Functions
    Player_State_Air    = Mod.GetPublicFunction(NULL, "Player_State_Air");
    Player_Input_P2_AI  = Mod.GetPublicFunction(NULL, "Player_Input_P2_AI");
    Player_TryTransform = Mod.GetPublicFunction(NULL, "Player_TryTransform");
    SaveGame_GetSaveRAM = Mod.GetPublicFunction(NULL, "SaveGame_GetSaveRAM");

    // Add Public Functions
    Mod.RegisterStateHook(Player_State_Air, Player_OldSuperInput, true);

    MOD_REGISTER_OBJECT_HOOK(Player);
    MOD_REGISTER_OBJECT_HOOK(HUD);
    MOD_REGISTER_OBJ_OVERLOAD(HUD, NULL, HUD_LateUpdate, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

#if RETRO_USE_MOD_LOADER
void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if GAME_VERSION == VER_100
    return false;
#else
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
#endif
}
#endif