#include "GameAPI/Game.h"
#include "Player.h"

ObjectPlayer *Player;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void Player_Draw(void)
{
    RSDK_THIS(Player);

    if (self->animator.rotationStyle == ROTSTYLE_FULL) {
        int32 rotStore = self->rotation;

        if (self->rotation >= 0x100)
            self->rotation = 0x200 - ((0x214 - self->rotation) >> 6 << 6);
        else
            self->rotation = (self->rotation + 20) >> 6 << 6;

        Mod.Super(Player->classID, SUPER_DRAW, NULL);

        self->rotation = rotStore;
    }
    else
        Mod.Super(Player->classID, SUPER_DRAW, NULL);
}

void InitModAPI(void) { MOD_REGISTER_OBJ_OVERLOAD(Player, NULL, NULL, NULL, Player_Draw, NULL, NULL, NULL, NULL, NULL); }

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