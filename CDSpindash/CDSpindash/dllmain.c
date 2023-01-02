#include "../GameAPI/C/GameAPI/Game.h"
#include "Player.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    Player_State_Ground   = Mod.GetPublicFunction(NULL, "Player_State_Ground");
    Player_State_Roll     = Mod.GetPublicFunction(NULL, "Player_State_Roll");
    Player_State_Spindash = Mod.GetPublicFunction(NULL, "Player_State_Spindash");
    Dust_State_SpinDash   = Mod.GetPublicFunction(NULL, "Dust_State_SpinDash");
    Camera_State_FollowY  = Mod.GetPublicFunction(NULL, "Camera_State_FollowY");

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_Crouch"), Player_Action_CDSpindash, false);
    Mod.RegisterStateHook(Player_State_Spindash, Player_State_CDSpindash, true);

    MOD_REGISTER_OBJECT_HOOK(Player);
    MOD_REGISTER_OBJ_OVERLOAD(Player, NULL, Player_LateUpdate, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
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