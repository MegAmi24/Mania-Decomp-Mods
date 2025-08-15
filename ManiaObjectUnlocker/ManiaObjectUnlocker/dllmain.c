#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Overloads.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void GameStartupCallback(void *data)
{
    UNUSED(data);

    InitUnlocks();
}

void InitModAPI(void)
{
    Mod.AddModCallback(MODCB_ONGAMESTARTUP, GameStartupCallback);
    ADD_PUBLIC_FUNC(CheckUnlock);
    RegisterOverloads();
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
