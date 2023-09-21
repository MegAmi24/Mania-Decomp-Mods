#include "../GameAPI/C/GameAPI/Game.h"
#include "ModConfig.h"

#include "Objects/Player.h"
#include "Objects/MegAmiMenu.h"
#include "Objects/DebugMode.h"
#include "Objects/Misc.h"

ModConfig config;

// Resolve externals
Hitbox *(*Player_GetAltHitbox)(EntityPlayer *player);
void (*Player_GiveRings)(EntityPlayer *player, int32 amount, bool32 playSfx);
void (*Player_ChangeCharacter)(EntityPlayer *player, int32 character);
bool32 (*Player_TryTransform)(EntityPlayer *player, uint8 emeraldMasks);
void (*Player_ApplyShield)(EntityPlayer *player);
StateMachine(Player_State_FlyToPlayer);
StateMachine(Player_State_ReturnToPlayer);
StateMachine(Player_Input_P1);
StateMachine(Player_Input_P2_Delay);
void (*Player_UpdatePhysicsState)(EntityPlayer *entity);
void (*Music_PlayJingle)(uint8 trackID);

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void StageLoadCallback(void *data)
{
    UNUSED(data);
    globals->notifiedAutosave = true;
    SceneInfo->debugMode      = true;
#if MANIA_USE_PLUS
    if (Mod.FindObject("Music") && SKU->platform != PLATFORM_DEV)
        RSDK.AddViewableVariable("Vape Mode", &globals->vapeMode, VIEWVAR_BOOL, false, true);
#endif
}

void DefaultCharacterCallback(void *data)
{
    UNUSED(data);

    uint8 leader  = ID_SONIC;
    uint8 sidekick = ID_TAILS;

    switch (config.defaultLeader) {
        default:
        case 0: leader = ID_SONIC; break;
        case 1: leader = ID_TAILS; break;
        case 2: leader = ID_KNUCKLES; break;
#if MANIA_USE_PLUS
        case 3: leader = API.CheckDLC(DLC_PLUS) ? ID_MIGHTY : ID_SONIC; break;
        case 4: leader = API.CheckDLC(DLC_PLUS) ? ID_RAY : ID_SONIC; break;
        case 5: leader = API.CheckDLC(DLC_PLUS) ? 1 << 5 : ID_SONIC; break;
#endif
    }

    switch (config.defaultSidekick) {
        default:
        case -1: sidekick = ID_NONE; break;
        case 0: sidekick = ID_SONIC; break;
        case 1: sidekick = ID_TAILS; break;
        case 2: sidekick = ID_KNUCKLES; break;
#if MANIA_USE_PLUS
        case 3: sidekick = API.CheckDLC(DLC_PLUS) ? ID_MIGHTY : ID_SONIC; break;
        case 4: sidekick = API.CheckDLC(DLC_PLUS) ? ID_RAY : ID_SONIC; break;
        case 5: sidekick = API.CheckDLC(DLC_PLUS) ? 1 << 5 : ID_SONIC; break;
#endif
    }

    globals->playerID = leader | sidekick << 8;
}

void InitModAPI(void)
{
    // Setup Config
    config.defaultLeader   = Mod.GetSettingsInteger("", "Config:defaultLeader", 0);
    config.defaultSidekick = Mod.GetSettingsInteger("", "Config:defaultSidekick", 1);

    uint8 characterCount = 2;
#if MANIA_USE_PLUS
    if (API.CheckDLC(DLC_PLUS)) {
        bool32 amyEnabled = false;
        bool32 modActive  = false;
        Mod.LoadModInfo("Extra Slot Amy", NULL, NULL, NULL, &modActive);
        amyEnabled |= modActive;
        Mod.LoadModInfo("Sonic Mania Addendum", NULL, NULL, NULL, &modActive);
        amyEnabled |= modActive;
        characterCount += 2 + amyEnabled;
    }
#endif

    Mod.SetSettingsInteger("Config:defaultLeader", CLAMP(config.defaultLeader, 0, characterCount));
    Mod.SetSettingsInteger("Config:defaultSidekick", CLAMP(config.defaultSidekick, -1, characterCount));
    Mod.SaveSettings();

    // Get Public Functions
    Player_Input_P1             = Mod.GetPublicFunction(NULL, "Player_Input_P1");
    Player_GetAltHitbox         = Mod.GetPublicFunction(NULL, "Player_GetAltHitbox");
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

    ADD_PUBLIC_FUNC(MegAmiMenu_HandleTouchControls);
    ADD_PUBLIC_FUNC(MegAmiMenu_CheckTouchRect);
    ADD_PUBLIC_FUNC(MegAmiMenu_HandleUpDown);
    ADD_PUBLIC_FUNC(MegAmiMenu_HandleSetValue);

    // Add Mod Callbacks
    Mod.AddModCallback(MODCB_ONSTAGELOAD, StageLoadCallback);
    Mod.AddModCallback(MODCB_ONGAMESTARTUP, DefaultCharacterCallback);

    // Register State Hooks
    Mod.RegisterStateHook(Player_Input_P1, Player_Input_P1_Hook, true);

    // Register Modded Objects
    MOD_REGISTER_OBJECT(MegAmiMenu, NULL, MegAmiMenu_Update, MegAmiMenu_LateUpdate, MegAmiMenu_StaticUpdate, MegAmiMenu_Draw, MegAmiMenu_Create,
                        MegAmiMenu_StageLoad, MegAmiMenu_EditorDraw, MegAmiMenu_EditorLoad, MegAmiMenu_Serialize);
    MOD_REGISTER_OBJ_OVERLOAD(Player, Player_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(DebugMode, DebugMode_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
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