#include "../GameAPI/C/GameAPI/Game.h"
#include "Player.h"
#include "Misc.h"

// Resolve externals
bool32 (*Player_CheckCollisionTouch)(EntityPlayer *player, void *e, Hitbox *entityHitbox);
StateMachine(Player_State_Ground);
StateMachine(Player_State_Roll);
StateMachine(Player_State_Spindash);
StateMachine(Camera_State_FollowY);

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    Player_CheckCollisionTouch = Mod.GetPublicFunction(NULL, "Player_CheckCollisionTouch");
    Player_State_Ground        = Mod.GetPublicFunction(NULL, "Player_State_Ground");
    Player_State_Roll          = Mod.GetPublicFunction(NULL, "Player_State_Roll");
    Player_State_Spindash      = Mod.GetPublicFunction(NULL, "Player_State_Spindash");
    Camera_State_FollowY       = Mod.GetPublicFunction(NULL, "Camera_State_FollowY");

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_Crouch"), Player_Action_CDSpindash, false);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "DashLift_State_HandleDash"), DashLift_State_HandleDash_Hook, true);

    ADD_PUBLIC_FUNC(Player_State_CDSpindash);

    MOD_REGISTER_OBJECT_HOOK(Player);
    MOD_REGISTER_OBJECT_HOOK(DashLift);
    MOD_REGISTER_OBJ_OVERLOAD(Player, NULL, Player_LateUpdate, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(SDashWheel, SDashWheel_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
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