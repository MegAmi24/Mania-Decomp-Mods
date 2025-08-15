#include "GameAPI/Game.h"
#include "Music.h"

bool32 (*Zone_IsZoneLastAct)(void) = NULL;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    Music_SetMusicTrack = Mod.GetPublicFunction(NULL, "Music_SetMusicTrack");
    Zone_IsZoneLastAct  = Mod.GetPublicFunction(NULL, "Zone_IsZoneLastAct");

    MOD_REGISTER_OBJECT_HOOK(Music);
    MOD_REGISTER_OBJ_OVERLOAD(Music, NULL, NULL, Music_StaticUpdate, NULL, NULL, Music_StageLoad, NULL, NULL, NULL);
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
