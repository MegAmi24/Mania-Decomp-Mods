#include "../GameAPI/C/GameAPI/Game.h"
#include "Music.h"
#include "Zone.h"

void (*Music_SetMusicTrack)(const char *path, uint8 track, uint32 loopPoint);

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    Music_SetMusicTrack = Mod.GetPublicFunction(NULL, "Music_SetMusicTrack");
    MOD_REGISTER_OBJECT_HOOK(Zone);
    MOD_REGISTER_OBJ_OVERLOAD(Zone, NULL, NULL, Zone_StaticUpdate, NULL, NULL, NULL, NULL, NULL, NULL);
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