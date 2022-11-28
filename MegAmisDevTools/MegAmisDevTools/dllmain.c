#include "../GameAPI/C/GameAPI/Game.h"

#include "Objects/Player.h"
#include "Objects/MegAmiMenu.h"
#include "Objects/Misc.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void StageLoadCallback(void *data)
{
    UNUSED(data);
    globals->notifiedAutosave = true;
    SceneInfo->debugMode = true;
}

void InitModAPI(void)
{
    // Get Public Functions
    Player_Input_P1             = Mod.GetPublicFunction(NULL, "Player_Input_P1");
    Player_GiveRings            = Mod.GetPublicFunction(NULL, "Player_GiveRings");
    Player_ChangeCharacter      = Mod.GetPublicFunction(NULL, "Player_ChangeCharacter");
    Player_TryTransform         = Mod.GetPublicFunction(NULL, "Player_TryTransform");
    Player_ApplyShield          = Mod.GetPublicFunction(NULL, "Player_ApplyShield");
    Player_State_FlyToPlayer    = Mod.GetPublicFunction(NULL, "Player_State_FlyToPlayer");
    Player_State_ReturnToPlayer = Mod.GetPublicFunction(NULL, "Player_State_ReturnToPlayer");
    Player_Input_P2_Delay       = Mod.GetPublicFunction(NULL, "Player_Input_P2_Delay");
    Player_UpdatePhysicsState   = Mod.GetPublicFunction(NULL, "Player_UpdatePhysicsState");
    Music_PlayJingle            = Mod.GetPublicFunction(NULL, "Music_PlayJingle");

    // Add Public Functions
    ADD_PUBLIC_FUNC(MegAmiMenu_State_Main);
    ADD_PUBLIC_FUNC(MegAmiMenu_State_P1Char);
    ADD_PUBLIC_FUNC(MegAmiMenu_State_P2Char);
    ADD_PUBLIC_FUNC(MegAmiMenu_State_Shield);
    ADD_PUBLIC_FUNC(MegAmiMenu_State_SetRings);

    ADD_PUBLIC_FUNC(MegAmiMenu_State_DrawChar);
    ADD_PUBLIC_FUNC(MegAmiMenu_State_DrawShield);
    ADD_PUBLIC_FUNC(MegAmiMenu_State_DrawSetValue);

    // Add Mod Callbacks
    Mod.AddModCallback(MODCB_ONSTAGELOAD, StageLoadCallback);

    // Register State Hooks
    Mod.RegisterStateHook(Player_Input_P1, Player_Input_P1_Hook, true);

    // Register Modded Objects
    MOD_REGISTER_OBJECT(MegAmiMenu, NULL, MegAmiMenu_Update, MegAmiMenu_LateUpdate, MegAmiMenu_StaticUpdate, MegAmiMenu_Draw, MegAmiMenu_Create,
                        MegAmiMenu_StageLoad, MegAmiMenu_EditorDraw, MegAmiMenu_EditorLoad, MegAmiMenu_Serialize);
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