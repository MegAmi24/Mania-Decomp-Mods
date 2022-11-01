#include "../GameAPI/C/GameAPI/Game.h"
#include "ModConfig.h"

#include "Objects/Player.h"
#include "Objects/HUD.h"
#include "Objects/Zone.h"
#include "Objects/Competition.h"
#include "Objects/CompetitionSession.h"
#include "Objects/GameOver.h"
#include "Objects/Camera.h"
#include "Objects/Ring.h"
#include "Objects/TitleCard.h"
#include "Objects/ItemBox.h"
#include "Objects/LRZConvItem.h"

ModConfig config;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    // Setup Config
    config.MaxHealth = Mod.GetSettingsInteger("", "Config:MaxHealth", 3);
    config.StartingHealth = Mod.GetSettingsInteger("", "Config:StartingHealth", 3);

    if (config.MaxHealth > 10) {
        Mod.SetSettingsInteger("Config:MaxHealth", 10);
    }
    else if (config.MaxHealth < 1) {
        Mod.SetSettingsInteger("Config:MaxHealth", 1);
    }
    else {
        Mod.SetSettingsInteger("Config:MaxHealth", config.MaxHealth);
    }

    if (config.StartingHealth > config.MaxHealth) {
        Mod.SetSettingsInteger("Config:StartingHealth", config.MaxHealth);
    }
    else if (config.StartingHealth < 1) {
        Mod.SetSettingsInteger("Config:StartingHealth", 1);
    }
    else {
        Mod.SetSettingsInteger("Config:StartingHealth", config.StartingHealth);
    }

    Mod.SaveSettings();

    Player_State_Hurt              = Mod.GetPublicFunction(NULL, "Player_State_Hurt");
    Player_State_Death             = Mod.GetPublicFunction(NULL, "Player_State_Death");
    HUD_State_MoveIn               = Mod.GetPublicFunction(NULL, "HUD_State_MoveIn");
    HUD_State_MoveOut              = Mod.GetPublicFunction(NULL, "HUD_State_MoveOut");
    HUD_CharacterIndexFromID       = Mod.GetPublicFunction(NULL, "HUD_CharacterIndexFromID");
    Ring_State_Lost                = Mod.GetPublicFunction(NULL, "Ring_State_Lost");
    Ring_State_LostFX              = Mod.GetPublicFunction(NULL, "Ring_State_LostFX");
    Ring_State_Big                 = Mod.GetPublicFunction(NULL, "Ring_State_Big");
    Zone_State_ReloadScene         = Mod.GetPublicFunction(NULL, "Zone_State_ReloadScene");
    Zone_TitleCard_SupressCB       = Mod.GetPublicFunction(NULL, "Zone_TitleCard_SupressCB");
    ItemBox_State_Break            = Mod.GetPublicFunction(NULL, "ItemBox_State_Break");
    ItemBox_State_IconFinish       = Mod.GetPublicFunction(NULL, "ItemBox_State_IconFinish");
    ItemBox_GivePowerup            = Mod.GetPublicFunction(NULL, "ItemBox_GivePowerup");
    ItemBox_HandleFallingCollision = Mod.GetPublicFunction(NULL, "ItemBox_HandleFallingCollision");
    LRZConvItem_HandleLRZConvPhys  = Mod.GetPublicFunction(NULL, "LRZConvItem_HandleLRZConvPhys");
    
    // Register State Hooks
    Mod.RegisterStateHook(HUD_State_MoveIn, HUD_State_MoveIn_Hook, false);
    Mod.RegisterStateHook(HUD_State_MoveOut, HUD_State_MoveOut_Hook, true);
    Mod.RegisterStateHook(Zone_State_ReloadScene, Zone_State_ReloadScene_Hook, false);
    Mod.RegisterStateHook(Zone_TitleCard_SupressCB, Zone_TitleCard_SupressCB_Hook, false);
    Mod.RegisterStateHook(ItemBox_State_Break, ItemBox_State_Break_Hook, true);

    MOD_REGISTER_OBJECT_HOOK(Player);
    MOD_REGISTER_OBJECT_HOOK(ItemBox);
    MOD_REGISTER_OBJECT_HOOK(HUD);
    MOD_REGISTER_OBJECT_HOOK(Zone);
    MOD_REGISTER_OBJECT_HOOK(TitleCard);

    MOD_REGISTER_OBJ_OVERLOAD_MSV(Player, Mod_Player, Player_Update, Player_LateUpdate, NULL, NULL, Player_Create, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(HUD, HUD_Update, NULL, NULL, HUD_Draw, HUD_Create, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(Ring, Ring_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    printf("Hello From Health Meter Initialization!\n");
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