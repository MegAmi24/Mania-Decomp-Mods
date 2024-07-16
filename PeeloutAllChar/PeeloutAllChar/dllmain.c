#include "GameAPI/Game.h"
#include "Player.h"

ObjectPlayer *Player;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void Player_Update(void)
{
    RSDK_THIS(Player);

    if (!self->statePeelout && globals->medalMods & MEDAL_PEELOUT)
        self->statePeelout = Mod.GetPublicFunction(NULL, "Player_Action_Peelout");

    Mod.Super(Player->classID, SUPER_UPDATE, NULL);
}

void InitModAPI(void) { MOD_REGISTER_OBJ_OVERLOAD(Player, Player_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); }

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