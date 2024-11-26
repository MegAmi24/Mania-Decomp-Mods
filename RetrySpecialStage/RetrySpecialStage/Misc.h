#ifndef OBJ_MISC_H
#define OBJ_MISC_H

#include "GameAPI/Game.h"

#define UICONTROL_BUTTON_COUNT (64)
#if MANIA_USE_PLUS
#define UICONTROL_PROMPT_COUNT (4)
#endif

#define UIDIALOG_OPTION_COUNT (3)

typedef struct {
    uint8 padding[0x58];

    int32 saveState;
    int32 characterID;
    int32 zoneID;
    int32 lives;
    int32 score;
    int32 score1UP;
    int32 chaosEmeralds;
    int32 continues;
    int32 storedStageID;
    int32 nextSpecialStage;
    int32 collectedSpecialRings;
    int32 medalMods;
#if MANIA_USE_PLUS
    //(AIZ if encore) + GHZ-TMZ + (ERZ if not encore)
    // Bonus stage is [28]
    // Special stage is [29]
    // the rest are unused
    int32 zoneTimes[32];
    int32 characterFlags;
    int32 stock;
    int32 playerID; // encore playerID
#endif
} SaveRAM;

typedef struct {
#if !MANIA_USE_PLUS
    RSDK_OBJECT
    Entity *loadEntityPtr;
    void (*loadCallback)(bool32 success);
    Entity *saveEntityPtr;
    void (*saveCallback)(void);
#else
    Entity *loadEntityPtr;
    void (*loadCallback)(bool32 success);
    Entity *saveEntityPtr;
    void (*saveCallback)(bool32 success);
#endif
    SaveRAM *saveRAM;
    int32 unused1;
} ObjectSaveGame;

typedef struct {
    RSDK_OBJECT
#if MANIA_USE_PLUS
    TABLE(color bgColors[21], { 0xF0C800, 0xF08C18, 0x80A0B0, 0x50D8A0, 0xF09018, 0x38B0C8, 0x38B0C8, 0xF07028, 0x50D8A0, 0xC83868, 0x50D8A0,
                                0xF09018, 0xC0C098, 0x38B0C8, 0x88A0B8, 0xA850F0, 0x88C801, 0x1B0F0,  0x50B098, 0x890C8,  0xE8B010 });
#else
    TABLE(color bgColors[15], { 0xF0C800, 0xF08C18, 0x80A0B0, 0x50D8A0, 0xF09018, 0x38B0C8, 0x38B0C8, 0xF07028, 0x50D8A0, 0xC83868, 0x50D8A0,
                                0xF09018, 0xC0C098, 0x38B0C8, 0x88A0B8 });
#endif
    color *activeColors;
    uint16 aniFrames;
} ObjectUIBackground;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
#if !MANIA_USE_PLUS
    uint16 continueFrames;
#endif
    uint16 sfxScoreAdd;
    uint16 sfxScoreTotal;
    uint16 sfxEvent;
    uint16 sfxSpecialWarp;
    uint16 sfxContinue;
    uint16 sfxEmerald;
} ObjectSpecialClear;

typedef struct {
    RSDK_OBJECT
} ObjectUIButton;

typedef struct {
    MANIA_UI_ITEM_BASE
    Vector2 size;
    int32 listID;
    int32 frameID;
    int32 align;
    int32 choiceCount;
    uint8 choiceDir;
    bool32 invisible;
    bool32 assignsP1;
    bool32 freeBindP2;
    bool32 transition;
    bool32 stopMusic;
    bool32 isDisabled;
    int32 bgEdgeSize;
    int32 textBounceOffset;
    int32 buttonBounceOffset;
    int32 textBounceVelocity;
    int32 buttonBounceVelocity;
    bool32 textVisible;
    bool32 clearParentState;
    Vector2 firstChoicePos;
    int32 selection;
    void (*choiceChangeCB)(void);
    Animator animator;
    uint16 textFrames;
    int32 startListID;
    int32 startFrameID;
} EntityUIButton;

typedef struct {
    RSDK_OBJECT
    bool32 isProcessingInput;
    bool32 inputLocked;
    bool32 lockInput;
    bool32 upPress[PLAYER_COUNT];
    bool32 downPress[PLAYER_COUNT];
    bool32 leftPress[PLAYER_COUNT];
    bool32 rightPress[PLAYER_COUNT];
    bool32 cancelPress[PLAYER_COUNT];
    bool32 acceptPress[PLAYER_COUNT];
    bool32 yPress[PLAYER_COUNT];
    bool32 xPress[PLAYER_COUNT];
#if MANIA_USE_PLUS
    bool32 startPress[PLAYER_COUNT];
#endif
    bool32 anyUpPress;
    bool32 anyDownPress;
    bool32 anyLeftPress;
    bool32 anyRightPress;
    bool32 anyConfirmPress;
    bool32 anyBackPress;
    bool32 anyYPress;
    bool32 anyXPress;
#if MANIA_USE_PLUS
    bool32 anyStartPress;
#endif
    bool32 forceBackPress;
    bool32 hasTouchInput;
    int32 timer;
    int32 unused1;
    uint16 aniFrames;
} ObjectUIControl;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 unused1;
    int32 buttonID;
    String tag;
    String parentTag;
    bool32 activeOnLoad;
    bool32 noWidgets;
    bool32 resetSelection;
    uint8 buttonCount;
#if MANIA_USE_PLUS
    uint8 promptCount;
#endif
    uint8 rowCount;
    uint8 columnCount;
    uint8 startingID;
    Vector2 size;
    Vector2 cameraOffset;
    Vector2 scrollSpeed;
#if MANIA_USE_PLUS
    bool32 noClamp;
    bool32 noWrap;
#endif
    Vector2 startPos;
    Vector2 targetPos;
    bool32 childHasFocus;
    bool32 dialogHasFocus;
#if MANIA_USE_PLUS
    bool32 popoverHasFocus;
#endif
    bool32 hasStoredButton;
    bool32 selectionDisabled;
#if MANIA_USE_PLUS
    bool32 menuWasSetup;
#endif
    int32 backoutTimer;
    int32 storedButtonID;
    int32 lastButtonID;
    void *heading;
    void *shifter;
#if MANIA_USE_PLUS
    void *carousel;
    void *prompts[UICONTROL_PROMPT_COUNT];
#endif
    void *buttons[UICONTROL_BUTTON_COUNT];
    bool32 (*backPressCB)(void);
    void (*processButtonInputCB)(void);
    void (*menuSetupCB)(void);
    void (*menuUpdateCB)(void);
    void (*yPressCB)(void);
    void (*xPressCB)(void);
    int32 unused2;
    int32 unused3;
    int32 unused4;
    int32 unused5;
    int32 unused6;
    int32 unused7;
} EntityUIControl;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 closeDelay;
    String textInfo;
    int32 buttonCount;
    Vector2 bgRectSize;
    Vector2 dialogPos;
    EntityUIControl *parent;
    Entity *entityPtr;
    uint8 buttonFrames[UIDIALOG_OPTION_COUNT];
    StateMachine(callbacks[UIDIALOG_OPTION_COUNT]);
    bool32 closeOnSelect[UIDIALOG_OPTION_COUNT];
    EntityUIButton *buttons[UIDIALOG_OPTION_COUNT];
    StateMachine(closeCB);
    bool32 playEventSfx;
    bool32 useAltColor;
    int32 lineLength[3];
    int32 lineCount;
    Animator animator;
} EntityUIDialog;

typedef struct {
    RSDK_OBJECT
    EntityUIDialog *activeDialog;
    EntityUIControl *controlStore;
    StateMachine(controlStateStore);
} ObjectUIDialog;

extern SaveRAM *(*SaveGame_GetSaveRAM)(void);
extern EntityUIDialog *(*UIDialog_CreateDialogYesNo)(String *text, void (*callbackYes)(void), void (*callbackNo)(void), bool32 closeOnSelect_Yes,
                                           bool32 closeOnSelect_No);

#endif
