#include "GameAPI/Game.h"

#include "Objects/UISaveSlot.h"
#include "Objects/UIMedallionPanel.h"
#include "Objects/SaveGame.h"
#include "Objects/GameProgress.h"
#include "Objects/Misc.h"

#if !MANIA_USE_PLUS
bool32 (*APICallback_GetConfirmButtonFlip)(void) = NULL;
#endif
void (*Localization_GetZoneName)(String *string, uint8 zone) = NULL;
void (*UIWaitSpinner_StartWait)(void) = NULL;
void (*UIWaitSpinner_FinishWait)(void) = NULL;
#if MANIA_USE_PLUS
int32 (*HUD_CharacterIndexFromID)(int32 characterID) = NULL;
int32 *(*SaveGame_GetDataPtr)(int32 slot, bool32 encore) = NULL;
void (*SaveGame_SaveFile)(void (*callback)(bool32 success)) = NULL;
#else
int32 *(*SaveGame_GetDataPtr)(int32 slot) = NULL;
void (*SaveGame_SaveFile)(void (*callback)(void)) = NULL;
#endif
EntityUIDialog *(*UIDialog_CreateDialogOk)(String *text, void (*callback)(void), bool32 closeOnSelect) = NULL;
EntityUIDialog *(*UIDialog_CreateDialogYesNo)(String *text, void (*callbackYes)(void), void (*callbackNo)(void), bool32 closeOnSelect_Yes,
                                              bool32 closeOnSelect_No) = NULL;
void (*UIDialog_CloseOnSel_HandleSelection)(EntityUIDialog *dialog, void (*callback)(void)) = NULL;
void (*UIControl_ClearInputs)(uint8 buttonID) = NULL;
ProgressRAM *(*GameProgress_GetProgressRAM)(void) = NULL;
void (*GameProgress_ClearBSSSave)(void) = NULL;
void (*GameProgress_MarkZoneCompleted)(int32 zoneID) = NULL;
void (*GameProgress_GiveEmerald)(int32 emeraldID) = NULL;
void (*GameProgress_GiveEnding)(uint8 ending) = NULL;
void (*GameProgress_GiveMedal)(uint8 medalID, uint8 type) = NULL;
#if MANIA_USE_PLUS
int32 (*CompetitionMenu_HandleUnlocks)(void) = NULL;
void (*ExtrasMenu_HandleUnlocks)(void) = NULL;
void (*MainMenu_HandleUnlocks)(void) = NULL;
void (*ManiaModeMenu_HandleUnlocks)(void) = NULL;
void (*OptionsMenu_HandleUnlocks)(void) = NULL;
void (*TimeAttackMenu_HandleUnlocks)(void) = NULL;
void (*UISubHeading_HandleUnlocks)(void) = NULL;
#else
void (*MenuSetup_HandleUnlocks)(void) = NULL;
#endif

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void InitModAPI(void)
{
    // Get Public Functions
#if !MANIA_USE_PLUS
    APICallback_GetConfirmButtonFlip = Mod.GetPublicFunction(NULL, "APICallback_GetConfirmButtonFlip");
#endif
    Localization_GetZoneName = Mod.GetPublicFunction(NULL, "Localization_GetZoneName");
    UISaveSlot_LoadSaveInfo  = Mod.GetPublicFunction(NULL, "UISaveSlot_LoadSaveInfo");
#if MANIA_USE_PLUS
    HUD_CharacterIndexFromID = Mod.GetPublicFunction(NULL, "HUD_CharacterIndexFromID");
#endif
    UIWaitSpinner_StartWait             = Mod.GetPublicFunction(NULL, "UIWaitSpinner_StartWait");
    UIWaitSpinner_FinishWait            = Mod.GetPublicFunction(NULL, "UIWaitSpinner_FinishWait");
    SaveGame_GetDataPtr                 = Mod.GetPublicFunction(NULL, "SaveGame_GetDataPtr");
    SaveGame_SaveFile                   = Mod.GetPublicFunction(NULL, "SaveGame_SaveFile");
    UIDialog_CreateDialogOk             = Mod.GetPublicFunction(NULL, "UIDialog_CreateDialogOk");
    UIDialog_CreateDialogYesNo          = Mod.GetPublicFunction(NULL, "UIDialog_CreateDialogYesNo");
    UIDialog_CloseOnSel_HandleSelection = Mod.GetPublicFunction(NULL, "UIDialog_CloseOnSel_HandleSelection");
    UIControl_ClearInputs               = Mod.GetPublicFunction(NULL, "UIControl_ClearInputs");
    GameProgress_GetProgressRAM         = Mod.GetPublicFunction(NULL, "GameProgress_GetProgressRAM");
    GameProgress_ClearBSSSave           = Mod.GetPublicFunction(NULL, "GameProgress_ClearBSSSave");
    GameProgress_MarkZoneCompleted      = Mod.GetPublicFunction(NULL, "GameProgress_MarkZoneCompleted");
    GameProgress_GiveEmerald            = Mod.GetPublicFunction(NULL, "GameProgress_GiveEmerald");
    GameProgress_GiveEnding             = Mod.GetPublicFunction(NULL, "GameProgress_GiveEnding");
    GameProgress_GiveMedal              = Mod.GetPublicFunction(NULL, "GameProgress_GiveMedal");
#if MANIA_USE_PLUS
    CompetitionMenu_HandleUnlocks = Mod.GetPublicFunction(NULL, "CompetitionMenu_HandleUnlocks");
    ExtrasMenu_HandleUnlocks      = Mod.GetPublicFunction(NULL, "ExtrasMenu_HandleUnlocks");
    MainMenu_HandleUnlocks        = Mod.GetPublicFunction(NULL, "MainMenu_HandleUnlocks");
    ManiaModeMenu_HandleUnlocks   = Mod.GetPublicFunction(NULL, "ManiaModeMenu_HandleUnlocks");
    OptionsMenu_HandleUnlocks     = Mod.GetPublicFunction(NULL, "OptionsMenu_HandleUnlocks");
    TimeAttackMenu_HandleUnlocks  = Mod.GetPublicFunction(NULL, "TimeAttackMenu_HandleUnlocks");
    UISubHeading_HandleUnlocks    = Mod.GetPublicFunction(NULL, "UISubHeading_HandleUnlocks");
#else
    MenuSetup_HandleUnlocks = Mod.GetPublicFunction(NULL, "MenuSetup_HandleUnlocks");
#endif

    // Add Public Functions
    ADD_PUBLIC_FUNC(UISaveSlot_SetupEditor);

    ADD_PUBLIC_FUNC(UISaveSlot_EditState_Main);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_ManiaChar);
#if MANIA_USE_PLUS
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_EncoreLeader);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_EncoreSidekick);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_EncoreStock);
#endif
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_Zone);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_SetLives);
#if MANIA_USE_PLUS
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_SetContinues);
#endif
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_SetScore);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_Emeralds);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_Wait);

    ADD_PUBLIC_FUNC(UISaveSlot_InitDLG_CB);
    ADD_PUBLIC_FUNC(UISaveSlot_CloseEditor_CB);
    ADD_PUBLIC_FUNC(UISaveSlot_InitSaveCB);
    ADD_PUBLIC_FUNC(UISaveSlot_Edit_ExitCB);

    ADD_PUBLIC_FUNC(UISaveSlot_DrawMenu);

    ADD_PUBLIC_FUNC(UISaveSlot_EditState_DrawChar);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_DrawZone);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_DrawSetValue);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_DrawEmeralds);

    ADD_PUBLIC_FUNC(UISaveSlot_HandleTouchControls);
    ADD_PUBLIC_FUNC(UISaveSlot_CheckTouchRect);
    ADD_PUBLIC_FUNC(UISaveSlot_HandleUpDown);
    ADD_PUBLIC_FUNC(UISaveSlot_HandleSetValue);

    ADD_PUBLIC_FUNC(UIMedallionPanel_State_Edit);
    ADD_PUBLIC_FUNC(UIMedallionPanel_State_Wait);

    ADD_PUBLIC_FUNC(UIMedallionPanel_CloseEditor_CB);
    ADD_PUBLIC_FUNC(UIMedallionPanel_Edit_ExitCB);

    ADD_PUBLIC_FUNC(UIMedallionPanel_DrawEditor);

    // Register State Hooks
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "UISaveSlot_State_ActiveSave"), UISaveSlot_State_Hook, true);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "UISaveSlot_State_CompletedSave"), UISaveSlot_State_Hook, true);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "UISaveSlot_State_NewSave"), UISaveSlot_State_Hook, true);

    // Register Modded Objects
    MOD_REGISTER_OBJ_OVERLOAD_MSV(UISaveSlot, Mod_UISaveSlot, NULL, NULL, NULL, NULL, NULL, UISaveSlot_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(UIMedallionPanel, Mod_UIMedallionPanel, UIMedallionPanel_Update, NULL, UIMedallionPanel_StaticUpdate,
                                  UIMedallionPanel_Draw, NULL, UIMedallionPanel_StageLoad, NULL, NULL, NULL);

    // Register Mod Callbacks
    Mod.AddModCallback(MODCB_ONDRAW, UISaveSlot_ModCB_OnDraw);
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
