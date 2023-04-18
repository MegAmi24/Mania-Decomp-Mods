#include "../GameAPI/C/GameAPI/Game.h"
#include "Player.h"
#if GAME_VERSION != VER_100
#include "HUD.h"
#endif

// Resolve externals
StateMachine(Player_State_Air);
StateMachine(Player_State_Transform);
StateMachine(Player_Input_P2_AI);
#if GAME_VERSION != VER_100
SaveRAM *(*SaveGame_GetSaveRAM)(void);
#endif

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    // Get Public Functions
    Player_State_Air       = Mod.GetPublicFunction(NULL, "Player_State_Air");
    Player_State_Transform = Mod.GetPublicFunction(NULL, "Player_State_Transform");
    Player_Input_P2_AI     = Mod.GetPublicFunction(NULL, "Player_Input_P2_AI");
#if GAME_VERSION != VER_100
    SaveGame_GetSaveRAM = Mod.GetPublicFunction(NULL, "SaveGame_GetSaveRAM");
#endif

    // Add Public Functions
    Mod.RegisterStateHook(Player_State_Air, Player_SuperCancel, true);

    MOD_REGISTER_OBJECT_HOOK(Player);
#if GAME_VERSION != VER_100
    MOD_REGISTER_OBJECT_HOOK(HUD);
    MOD_REGISTER_OBJ_OVERLOAD(HUD, NULL, HUD_LateUpdate, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
#endif
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