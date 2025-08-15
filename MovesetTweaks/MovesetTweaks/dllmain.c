#include "GameAPI/Game.h"
#include "Player.h"

SaveRAM *(*SaveGame_GetSaveRAM)(void) = NULL;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    Player_Action_Jump      = Mod.GetPublicFunction(NULL, "Player_Action_Jump");
    Player_Action_Spindash  = Mod.GetPublicFunction(NULL, "Player_Action_Spindash");
    Player_State_Air        = Mod.GetPublicFunction(NULL, "Player_State_Air");
    Player_State_FlyCarried = Mod.GetPublicFunction(NULL, "Player_State_FlyCarried");
    Player_Input_P2_AI      = Mod.GetPublicFunction(NULL, "Player_Input_P2_AI");
    Player_Input_P2_Player  = Mod.GetPublicFunction(NULL, "Player_Input_P2_Player");

    SaveGame_GetSaveRAM = Mod.GetPublicFunction(NULL, "SaveGame_GetSaveRAM");

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_JumpAbility_Sonic"), Player_JumpAbility_Sonic_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_TailsFlight"), Player_State_TailsFlight_Hook, false);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_KnuxGlideDrop"), Player_State_KnuxGlideDrop_Hook, false);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_KnuxGlideSlide"), Player_State_KnuxGlideSlide_Hook, false);

    ADD_PUBLIC_FUNC(Player_GroundActionControls);
    ADD_PUBLIC_FUNC(Player_CanTransform);

    MOD_REGISTER_OBJECT_HOOK(Player);

    // Support for Super Cancel
    Mod.LoadModInfo("SuperCancel", NULL, NULL, NULL, &superCancel);
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
