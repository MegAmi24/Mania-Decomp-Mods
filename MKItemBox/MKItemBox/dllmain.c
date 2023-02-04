#include "../GameAPI/C/GameAPI/Game.h"

#include "ItemBox.h"
#include "Misc.h"
#include "Player.h"

// Resolve externals
StateMachine(ItemBox_DebugDraw);
StateMachine(ItemBox_DebugSpawn);
void (*ItemBox_CheckHit)(void);
void (*ItemBox_GivePowerup)(void);
void (*ItemBox_Break)(EntityItemBox *itemBox, EntityPlayer *player);
bool32 (*ItemBox_HandleFallingCollision)(void);
bool32 (*ItemBox_HandlePlatformCollision)(void *platform);
void (*ItemBox_HandleObjectCollisions)(void);
StateMachine(ItemBox_State_Broken);
StateMachine(ItemBox_State_Break);
StateMachine(ItemBox_State_IconFinish);
StateMachine(ItemBox_State_Idle);
StateMachine(ItemBox_State_Falling);
StateMachine(ItemBox_State_Conveyor);
int32 (*BadnikHelpers_Oscillate)(int32 origin, int32 speed, int32 amplitude);
Vector2 (*LRZConvItem_HandleLRZConvPhys)(void *e);
StateMachine(Debris_State_Fall);
bool32 (*Player_CheckCollisionTouch)(EntityPlayer *player, void *entity, Hitbox *entityHitbox);

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    ItemBox_State_Broken     = Mod.GetPublicFunction(NULL, "ItemBox_State_Broken");
    ItemBox_State_Break      = Mod.GetPublicFunction(NULL, "ItemBox_State_Break");
    ItemBox_State_IconFinish = Mod.GetPublicFunction(NULL, "ItemBox_State_IconFinish");
    ItemBox_State_Idle       = Mod.GetPublicFunction(NULL, "ItemBox_State_Idle");
    ItemBox_State_Falling    = Mod.GetPublicFunction(NULL, "ItemBox_State_Falling");
    ItemBox_State_Conveyor   = Mod.GetPublicFunction(NULL, "ItemBox_State_Conveyor");

    ItemBox_DebugDraw               = Mod.GetPublicFunction(NULL, "ItemBox_DebugDraw");
    ItemBox_DebugSpawn              = Mod.GetPublicFunction(NULL, "ItemBox_DebugSpawn");
    ItemBox_CheckHit                = Mod.GetPublicFunction(NULL, "ItemBox_CheckHit");
    ItemBox_GivePowerup             = Mod.GetPublicFunction(NULL, "ItemBox_GivePowerup");
    ItemBox_Break                   = Mod.GetPublicFunction(NULL, "ItemBox_Break");
    ItemBox_HandleFallingCollision  = Mod.GetPublicFunction(NULL, "ItemBox_HandleFallingCollision");
    ItemBox_HandlePlatformCollision = Mod.GetPublicFunction(NULL, "ItemBox_HandlePlatformCollision");
    ItemBox_HandleObjectCollisions  = Mod.GetPublicFunction(NULL, "ItemBox_HandleObjectCollisions");
    ItemBox_GivePowerup             = Mod.GetPublicFunction(NULL, "ItemBox_GivePowerup");
    ItemBox_HandleFallingCollision  = Mod.GetPublicFunction(NULL, "ItemBox_HandleFallingCollision");
    LRZConvItem_HandleLRZConvPhys   = Mod.GetPublicFunction(NULL, "LRZConvItem_HandleLRZConvPhys");

    Player_CheckCollisionTouch = Mod.GetPublicFunction(NULL, "Player_CheckCollisionTouch");
    Debris_State_Fall          = Mod.GetPublicFunction(NULL, "Debris_State_Fall");
    BadnikHelpers_Oscillate    = Mod.GetPublicFunction(NULL, "BadnikHelpers_Oscillate");

    Mod.RegisterStateHook(ItemBox_State_IconFinish, ItemBox_State_IconFinish_Hook, true);
    Mod.RegisterStateHook(ItemBox_State_Idle, ItemBox_State_Idle_Hook, true);
    Mod.RegisterStateHook(ItemBox_State_Falling, ItemBox_State_Falling_Hook, true);
    Mod.RegisterStateHook(ItemBox_State_Conveyor, ItemBox_State_Conveyor_Hook, true);

    MOD_REGISTER_OBJECT_HOOK(ItemBox);

    ADD_PUBLIC_FUNC(ItemBox_CheckHit_New);
    ADD_PUBLIC_FUNC(ItemBox_Break_New);
    ADD_PUBLIC_FUNC(ItemBox_HandleBox);

    MOD_REGISTER_OBJ_OVERLOAD_MSV(ItemBox, Mod_ItemBox, NULL, NULL, ItemBox_StaticUpdate, ItemBox_Draw, NULL, ItemBox_StageLoad, NULL, NULL, NULL);
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