#include "GameAPI/Game.h"
#include "UFO_HUD.h"

ObjectUFO_HUD *UFO_HUD;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void UFO_HUD_Update(void)
{
    bool32 yPress              = ControllerInfo->keyY.press;
    ControllerInfo->keyY.press = false;
    Mod.Super(UFO_HUD->classID, SUPER_UPDATE, NULL);
    ControllerInfo->keyY.press = yPress;
}

void InitModAPI(void) { MOD_REGISTER_OBJ_OVERLOAD(UFO_HUD, UFO_HUD_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); }

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