#include "../GameAPI/C/GameAPI/Game.h"
#include "DebugMode.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    Zone_StartFadeOut_MusicFade = Mod.GetPublicFunction(NULL, "Zone_StartFadeOut_MusicFade");

    MOD_REGISTER_OBJECT_HOOK(DebugMode);
    MOD_REGISTER_OBJ_OVERLOAD(DebugMode, DebugMode_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
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