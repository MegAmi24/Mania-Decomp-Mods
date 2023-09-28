#include "GameAPI/Game.h"
#include "ModConfig.h"

#include "Objects/Player.h"
#include "Objects/HUD.h"
#include "Objects/Ring.h"
#include "Objects/ItemBox.h"
#include "Objects/Misc.h"

ModConfig config;

// Resolve externals
StateMachine(HUD_State_MoveIn);
StateMachine(HUD_State_MoveOut);
int32 (*HUD_CharacterIndexFromID)(int32 characterID);
StateMachine(Player_State_Hurt);
StateMachine(Player_State_Death);
StateMachine(ItemBox_State_Break);
StateMachine(Ring_State_Lost);
StateMachine(Ring_State_LostFX);
StateMachine(Ring_State_Big);
void (*CompSession_DeriveWinner)(int32 playerID, int32 finishType);
Vector2 (*LRZConvItem_HandleLRZConvPhys)(void *e);
StateMachine(Zone_TitleCard_SupressCB);
StateMachine(Zone_State_ReloadScene);

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    // Setup Config
    config.MaxHealth      = Mod.GetSettingsInteger("", "Config:MaxHealth", 3);
    config.StartingHealth = Mod.GetSettingsInteger("", "Config:StartingHealth", 3);

    Mod.SetSettingsInteger("Config:MaxHealth", CLAMP(config.MaxHealth, 1, 10));
    Mod.SetSettingsInteger("Config:StartingHealth", CLAMP(config.StartingHealth, 1, config.MaxHealth));
    Mod.SaveSettings();

    Player_State_Hurt             = Mod.GetPublicFunction(NULL, "Player_State_Hurt");
    Player_State_Death            = Mod.GetPublicFunction(NULL, "Player_State_Death");
    HUD_State_MoveIn              = Mod.GetPublicFunction(NULL, "HUD_State_MoveIn");
    HUD_State_MoveOut             = Mod.GetPublicFunction(NULL, "HUD_State_MoveOut");
    HUD_CharacterIndexFromID      = Mod.GetPublicFunction(NULL, "HUD_CharacterIndexFromID");
    Ring_State_Lost               = Mod.GetPublicFunction(NULL, "Ring_State_Lost");
    Ring_State_LostFX             = Mod.GetPublicFunction(NULL, "Ring_State_LostFX");
    Ring_State_Big                = Mod.GetPublicFunction(NULL, "Ring_State_Big");
    Zone_State_ReloadScene        = Mod.GetPublicFunction(NULL, "Zone_State_ReloadScene");
    Zone_TitleCard_SupressCB      = Mod.GetPublicFunction(NULL, "Zone_TitleCard_SupressCB");
    ItemBox_State_Break           = Mod.GetPublicFunction(NULL, "ItemBox_State_Break");
    LRZConvItem_HandleLRZConvPhys = Mod.GetPublicFunction(NULL, "LRZConvItem_HandleLRZConvPhys");
#if !MANIA_USE_PLUS
    CompSession_DeriveWinner = Mod.GetPublicFunction(NULL, "CompetitionSession_DeriveWinner");
#else
    CompSession_DeriveWinner = Mod.GetPublicFunction(NULL, "Competition_DeriveWinner");
#endif

    // Register State Hooks
    Mod.RegisterStateHook(HUD_State_MoveIn, HUD_State_MoveIn_Hook, false);
    Mod.RegisterStateHook(HUD_State_MoveOut, HUD_State_MoveOut_Hook, false);
    Mod.RegisterStateHook(Zone_State_ReloadScene, Zone_State_ReloadScene_Hook, false);
    Mod.RegisterStateHook(Zone_TitleCard_SupressCB, Zone_TitleCard_SupressCB_Hook, false);
    Mod.RegisterStateHook(ItemBox_State_Break, ItemBox_State_Break_Hook, true);

    MOD_REGISTER_OBJECT_HOOK(Player);
    MOD_REGISTER_OBJECT_HOOK(ItemBox);
    MOD_REGISTER_OBJECT_HOOK(HUD);
    MOD_REGISTER_OBJECT_HOOK(Zone);
    MOD_REGISTER_OBJECT_HOOK(TitleCard);

    MOD_REGISTER_OBJ_OVERLOAD_MSV(Player, Mod_Player, Player_Update, Player_LateUpdate, NULL, NULL, Player_Create, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(HUD, Mod_HUD, HUD_Update, NULL, NULL, HUD_Draw, HUD_Create, HUD_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(ItemBox, NULL, NULL, NULL, NULL, NULL, ItemBox_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(Ring, NULL, Ring_LateUpdate, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
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