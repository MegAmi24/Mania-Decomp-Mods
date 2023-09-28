#include "GameAPI/Game.h"
#include "Player.h"

// Resolve externals
void (*Player_ApplyShield)(EntityPlayer *player);
StateMachine(Player_State_Air);
StateMachine(Player_State_BubbleBounce);
StateMachine(Player_JumpAbility_Sonic);

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void EnableInstaShield(void *data)
{
    UNUSED(data);

    globals->medalMods |= MEDAL_INSTASHIELD;
}

void InitModAPI(void)
{
    // Register State Hooks
    Mod.AddModCallback(MODCB_ONSTAGELOAD, EnableInstaShield);

    // Get Public Functions
    Player_State_Air          = Mod.GetPublicFunction(NULL, "Player_State_Air");
    Player_JumpAbility_Sonic  = Mod.GetPublicFunction(NULL, "Player_JumpAbility_Sonic");
    Player_ApplyShield        = Mod.GetPublicFunction(NULL, "Player_ApplyShield");
    Player_State_BubbleBounce = Mod.GetPublicFunction(NULL, "Player_State_BubbleBounce");

    // Add Public Functions
    ADD_PUBLIC_FUNC(Player_JumpAbility_SonicShieldControl);
    ADD_PUBLIC_FUNC(Player_State_NoShieldBounce);

    MOD_REGISTER_OBJECT_HOOK(Player);
    MOD_REGISTER_OBJ_OVERLOAD(Player, Player_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
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