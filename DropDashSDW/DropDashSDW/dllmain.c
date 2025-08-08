#include "GameAPI/Game.h"
#include "Player.h"
#include "SDashWheel.h"

bool32 (*Player_CheckCollisionBox)(EntityPlayer *player, void *entity, Hitbox *entityHitbox) = NULL;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    Player_CheckCollisionBox = Mod.GetPublicFunction(NULL, "Player_CheckCollisionBox");

    MOD_REGISTER_OBJECT_HOOK(Player);
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
