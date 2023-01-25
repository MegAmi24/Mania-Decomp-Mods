#include "../GameAPI/C/GameAPI/Game.h"
#include "PullChain.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    ADD_PUBLIC_FUNC(PullChain_HandleDunkeyCode);

    MOD_REGISTER_OBJECT_HOOK(PullChain);
    MOD_REGISTER_OBJ_OVERLOAD(PullChain, PullChain_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

#if RETRO_USE_MOD_LOADER
void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if GAME_VERSION != VER_100
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
#else
    return false;
#endif
}
#endif