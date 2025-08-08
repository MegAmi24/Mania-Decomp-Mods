#include "GameAPI/Game.h"
#include "Player.h"
#include "Shield.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    Player_State_Air      = Mod.GetPublicFunction(NULL, "Player_State_Air");
    Player_State_DropDash = Mod.GetPublicFunction(NULL, "Player_State_DropDash");
    Shield_State_Insta    = Mod.GetPublicFunction(NULL, "Shield_State_Insta");

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_Roll"), Player_SetRollJumpLock, false);

    ADD_PUBLIC_FUNC(Player_State_RollingAir);
    ADD_PUBLIC_FUNC(Player_State_RollingDropDash);

    MOD_REGISTER_OBJECT_HOOK(Player);
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