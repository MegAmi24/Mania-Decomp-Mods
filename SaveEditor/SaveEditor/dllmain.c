#include "GameAPI/Game.h"

#include "Objects/UISaveSlot.h"
#include "Objects/SaveGame.h"
#include "Objects/Misc.h"

// Resolve externals
#if !MANIA_USE_PLUS
bool32 (*APICallback_GetConfirmButtonFlip)(void);
#endif
void (*Localization_GetZoneName)(String *string, uint8 zone);
void (*UISaveSlot_LoadSaveInfo)(void);
void (*UIWaitSpinner_StartWait)(void);
void (*UIWaitSpinner_FinishWait)(void);
#if MANIA_USE_PLUS
int32 (*HUD_CharacterIndexFromID)(int32 characterID);
int32 *(*SaveGame_GetDataPtr)(int32 slot, bool32 encore);
void (*SaveGame_SaveFile)(void (*callback)(bool32 success));
#else
int32 *(*SaveGame_GetDataPtr)(int32 slot);
void (*SaveGame_SaveFile)(void (*callback)(void));
#endif
EntityUIDialog *(*UIDialog_CreateDialogOk)(String *text, void (*callback)(void), bool32 closeOnSelect);
EntityUIDialog *(*UIDialog_CreateDialogYesNo)(String *text, void (*callbackYes)(void), void (*callbackNo)(void), bool32 closeOnSelect_Yes,
                                              bool32 closeOnSelect_No);
void (*UIDialog_CloseOnSel_HandleSelection)(EntityUIDialog *dialog, void (*callback)(void));

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
    ADD_PUBLIC_FUNC(UISaveSlot_Edit_BackCB);

    ADD_PUBLIC_FUNC(UISaveSlot_DrawMenu);

    ADD_PUBLIC_FUNC(UISaveSlot_EditState_DrawChar);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_DrawZone);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_DrawSetValue);
    ADD_PUBLIC_FUNC(UISaveSlot_EditState_DrawEmeralds);

    ADD_PUBLIC_FUNC(UISaveSlot_HandleTouchControls);
    ADD_PUBLIC_FUNC(UISaveSlot_CheckTouchRect);
    ADD_PUBLIC_FUNC(UISaveSlot_HandleUpDown);
    ADD_PUBLIC_FUNC(UISaveSlot_HandleSetValue);

    // Register State Hooks
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "UISaveSlot_State_ActiveSave"), UISaveSlot_State_Hook, true);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "UISaveSlot_State_CompletedSave"), UISaveSlot_State_Hook, true);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "UISaveSlot_State_NewSave"), UISaveSlot_State_Hook, true);

    // Register Modded Objects
    MOD_REGISTER_OBJ_OVERLOAD_MSV(UISaveSlot, Mod_UISaveSlot, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

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