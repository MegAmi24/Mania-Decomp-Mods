#ifndef OBJ_SAVEEDITOR_H
#define OBJ_SAVEEDITOR_H

#include "GameAPI/Game.h"
#include "SaveGame.h"
#include "Misc.h"

#if MANIA_USE_PLUS
#define API_GetConfirmButtonFlip API.GetConfirmButtonFlip
#else
#define API_GetConfirmButtonFlip APICallback_GetConfirmButtonFlip
#endif

#define MAINBOX_XPOS   (16)
#define MAINBOX_WIDTH  (90)
#define SUBBOX_XPOS    (MAINBOX_XPOS + MAINBOX_WIDTH + 3)
#define BOX_YPOS       (12)
#define OPTION_SPACING (14)
#define BOX_HEIGHT(x)  ((x)*OPTION_SPACING + 5) // x = Option Count

#if MANIA_USE_PLUS
#define LoadSaveRAM() SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID, self->encoreMode);
#else
#define LoadSaveRAM() (SaveRAM *)SaveGame_GetDataPtr(self->slotID);
#endif

#define AddMenuOption(option, string)                                                                                                                \
    Mod_UISaveSlot->menuCount++;                                                                                                                     \
    Mod_UISaveSlot->menuOptions[Mod_UISaveSlot->menuCount] = option;                                                                                 \
    RSDK.InitString(&Mod_UISaveSlot->menuStrings[Mod_UISaveSlot->menuCount], string, false);

#define ExitSubMenu()                                                                                                                                \
    Mod_UISaveSlot->state     = UISaveSlot_EditState_Main;                                                                                           \
    Mod_UISaveSlot->stateDraw = StateMachine_None;                                                                                                   \
    UISaveSlot_LoadSaveInfo();

#define DrawOptionText(string)                                                                                                                       \
    RSDK.DrawText(&Mod_UISaveSlot->animator, &drawPos, string, 0, string.length, ALIGN_LEFT, 0, 0, 0, true);                                         \
    drawPos.y += TO_FIXED(OPTION_SPACING);

#define confirmPress                                                                                                                                 \
    (ControllerInfo[CONT_P1].keyStart.press || (API_GetConfirmButtonFlip() ? ControllerInfo[CONT_P1].keyB.press : ControllerInfo[CONT_P1].keyA.press))
#define backPress (API_GetConfirmButtonFlip() ? ControllerInfo[CONT_P1].keyA.press : ControllerInfo[CONT_P1].keyB.press)

#define Y_THIRD (ScreenInfo->size.y / 3)

typedef enum {
    SAVEEDITOR_CHAR,
#if MANIA_USE_PLUS
    SAVEEDITOR_LEADER,
    SAVEEDITOR_SIDEKICK,
    SAVEEDITOR_STOCK1,
    SAVEEDITOR_STOCK2,
    SAVEEDITOR_STOCK3,
#endif
    SAVEEDITOR_ZONE,
    SAVEEDITOR_LIVES,
#if MANIA_USE_PLUS
    SAVEEDITOR_CONTINUES,
#endif
    SAVEEDITOR_SCORE,
    SAVEEDITOR_EMERALDS,
    SAVEEDITOR_EXIT,
    SAVEEDITOR_COUNT,
} SaveEditorOptions;

typedef enum {
    CHARACTER_SONIC_TAILS,
    CHARACTER_SONIC,
    CHARACTER_TAILS,
    CHARACTER_KNUCKLES,
#if MANIA_USE_PLUS
    CHARACTER_MIGHTY,
    CHARACTER_RAY,
    CHARACTER_NONE,
#endif
    CHARACTER_COUNT,
} CharacterStrings;

typedef enum {
    UISAVESLOT_REGULAR,
    UISAVESLOT_NOSAVE,
} UISaveSlotTypes;

typedef enum {
    ZONE_INVALID = -1,
    ZONE_GHZ,
    ZONE_CPZ,
    ZONE_SPZ,
    ZONE_FBZ,
    ZONE_PGZ,
    ZONE_SSZ,
    ZONE_HCZ,
    ZONE_MSZ,
    ZONE_OOZ,
    ZONE_LRZ,
    ZONE_MMZ,
    ZONE_TMZ,
    ZONE_ERZ,
#if MANIA_USE_PLUS
    ZONE_AIZ,
#endif
    // total zone count
    ZONE_COUNT,
    // zone count for save files
    ZONE_COUNT_SAVEFILE = ZONE_ERZ + 1,
} ZoneIDs;

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectUISaveSlot;

// Mod Object Class
typedef struct {
    StateMachine(state);
    StateMachine(stateDraw);
#if MANIA_USE_PLUS
    StateMachine(stateInputStore);
#endif
    bool32 (*backPressCBStore)(void);
    StateMachine(yPressCBStore);
    int8 mainSelection;
    int8 subSelection;
    int32 customValue;
    uint8 valueDigits;
    int8 menuCount;
    int8 menuOptions[SAVEEDITOR_COUNT];
    String menuStrings[SAVEEDITOR_COUNT];
    String charStrings[CHARACTER_COUNT];
    String zoneStrings[ZONE_COUNT_SAVEFILE];
    Animator animator;
    Animator emeraldsAnimator;
    uint16 aniFrames;
    bool32 anyUpPress;
    bool32 anyDownPress;
    bool32 anyLeftPress;
    bool32 anyRightPress;
    bool32 anyConfirmPress;
    bool32 anyBackPress;
    bool32 anyYPress;
    bool32 anyXPress;
    uint8 touchUp;
    uint8 touchDown;
    uint8 touchLeft;
    uint8 touchRight;
    uint8 touchConfirm;
    uint8 touchBack;
} ModObjectUISaveSlot;

// Entity Class
typedef struct {
    MANIA_UI_ITEM_BASE
    bool32 isNewSave;
#if MANIA_USE_PLUS
    StateMachine(stateInput);
#endif
    int32 listID;
    int32 frameID;
    int32 saveZoneID;
    int32 saveLives;
#if MANIA_USE_PLUS
    int32 saveContinues;
#endif
    int32 saveEmeralds;
#if MANIA_USE_PLUS
    uint8 saveEncorePlayer;
    uint8 saveEncoreBuddy;
    uint8 saveEncoreFriends[3];
#endif
    UISaveSlotTypes type;
    int32 slotID;
#if MANIA_USE_PLUS
    bool32 encoreMode;
#endif
    bool32 currentlySelected;
    int32 zoneIconSprX;
    int32 textBounceOffset;
    int32 buttonBounceOffset;
    int32 textBouncePos;
    int32 buttonBouncePos;
    int32 fxRadius;
#if MANIA_USE_PLUS
    EntityFXRuby *fxRuby;
    bool32 debugEncoreDraw;
    uint8 dCharPoint;
    uint8 dCharPartner;
    uint8 dCharStock1;
    uint8 dCharStock2;
    uint8 dCharStock3;
#endif
    Animator uiAnimator;
    Animator playersAnimator;
    Animator shadowsAnimator;
    Animator livesAnimator;
#if MANIA_USE_PLUS
    Animator continuesAnimator;
#endif
    Animator emeraldsAnimator;
    Animator zoneIconAnimator;
    Animator zoneNameAnimator;
    Animator fuzzAnimator;
    Animator iconBGAnimator;
    Animator saveStatusAnimator;
    Animator numbersAnimator;
    uint16 textFrames;
} EntityUISaveSlot;

// Object Struct
extern ObjectUISaveSlot *UISaveSlot;
extern ModObjectUISaveSlot *Mod_UISaveSlot;

// State Hooks
bool32 UISaveSlot_State_Hook(bool32 skipped);

// States
void UISaveSlot_EditState_Main(void);
void UISaveSlot_EditState_ManiaChar(void);
#if MANIA_USE_PLUS
void UISaveSlot_EditState_EncoreLeader(void);
void UISaveSlot_EditState_EncoreSidekick(void);
void UISaveSlot_EditState_EncoreStock(void);
#endif
void UISaveSlot_EditState_Zone(void);
void UISaveSlot_EditState_SetLives(void);
#if MANIA_USE_PLUS
void UISaveSlot_EditState_SetContinues(void);
#endif
void UISaveSlot_EditState_SetScore(void);
void UISaveSlot_EditState_Emeralds(void);
void UISaveSlot_EditState_Wait(void);

void UISaveSlot_CloseEditor_CB(void);
#if MANIA_USE_PLUS
void UISaveSlot_Edit_ExitCB(bool32 success);
#else
void UISaveSlot_Edit_ExitCB(void);
#endif

void UISaveSlot_ModCB_OnStaticUpdate(void *data);

// Draw States
void UISaveSlot_ModCB_OnDraw(void *data);
void UISaveSlot_DrawMenu(void);

void UISaveSlot_EditState_DrawChar(void);
void UISaveSlot_EditState_DrawZone(void);
void UISaveSlot_EditState_DrawSetValue(void);
void UISaveSlot_EditState_DrawEmeralds(void);

// Extra Entity Functions
void UISaveSlot_HandleTouchControls(void);
bool32 UISaveSlot_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2);
void UISaveSlot_HandleUpDown(int8 maxCount);
void UISaveSlot_HandleSetValue(int32 minValue, int32 maxValue);

#if MANIA_USE_PLUS
void UISaveSlot_SetCharacterFlags(SaveRAM *saveRAM);
#endif
void UISaveSlot_ClearInputs(void);

#if !MANIA_USE_PLUS
extern bool32 (*APICallback_GetConfirmButtonFlip)(void);
#endif
extern void (*Localization_GetZoneName)(String *string, uint8 zone);
extern void (*UISaveSlot_LoadSaveInfo)(void);
#if MANIA_USE_PLUS
extern int32 (*HUD_CharacterIndexFromID)(int32 characterID);
#endif
extern void (*UIWaitSpinner_StartWait)(void);
extern void (*UIWaitSpinner_FinishWait)(void);

#endif //! OBJ_SAVEEDITOR_H
