#include "GameAPI/Game.h"
#include "Player.h"

ObjectPlayer *Player;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void Player_Create(void *data)
{
    RSDK_THIS(Player);

    Mod.Super(Player->classID, SUPER_CREATE, data);

    if (!self->statePeelout && globals->medalMods & MEDAL_PEELOUT)
        self->statePeelout = Mod.GetPublicFunction(NULL, "Player_Action_Peelout");
}

void InitModAPI(void) { MOD_REGISTER_OBJ_OVERLOAD(Player, NULL, NULL, NULL, NULL, Player_Create, NULL, NULL, NULL, NULL); }

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