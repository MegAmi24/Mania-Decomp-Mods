#ifndef OBJ_MISC_H
#define OBJ_MISC_H

#include "GameAPI/Game.h"
#include "UISaveSlot.h"

#define UICONTROL_BUTTON_COUNT (64)
#if MANIA_USE_PLUS
#define UICONTROL_PROMPT_COUNT (4)
#endif

#define UIDIALOG_OPTION_COUNT (3)

#if MANIA_USE_PLUS
#define Menu_HandleUnlocks                                                                                                                           \
    CompetitionMenu_HandleUnlocks();                                                                                                                 \
    ExtrasMenu_HandleUnlocks();                                                                                                                      \
    MainMenu_HandleUnlocks();                                                                                                                        \
    ManiaModeMenu_HandleUnlocks();                                                                                                                   \
    OptionsMenu_HandleUnlocks();                                                                                                                     \
    TimeAttackMenu_HandleUnlocks();                                                                                                                  \
    UISubHeading_HandleUnlocks
#else
#define Menu_HandleUnlocks MenuSetup_HandleUnlocks
#endif

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
    void *buttons[UIDIALOG_OPTION_COUNT];
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

typedef struct {
    RSDK_OBJECT
#if MANIA_USE_PLUS
    int32 buttonColors[16];
    int32 timer;
    Animator unusedAnimator1;
    Animator unusedAnimator2;
#else
    int32 timer;
    int32 buttonColors[16];
#endif
    Animator frameAnimator;
    Animator arrowsAnimator;
    uint16 uiFrames;
#if MANIA_USE_PLUS
    uint16 saveSelFrames;
#endif
    uint16 textFrames;
    uint16 fontFrames;
    uint16 sfxBleep;
    uint16 sfxAccept;
    uint16 sfxWarp;
    uint16 sfxEvent;
    uint16 sfxWoosh;
    uint16 sfxFail;
#if MANIA_USE_PLUS
    color buttonColor;
#endif
} ObjectUIWidgets;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 unused1;
    int32 radiusSpeed;
    int32 radius;
    int32 innerRadius;
    int32 outerRadius;
    int32 timer;
    int32 delay;
    int32 fadeWhite;
    int32 fadeBlack;
    bool32 waitForTrigger;
    int32 unused2;
    int32 unused3;
    int32 unused4;
    bool32 fullyExpanded;
} EntityFXRuby;

// Object Class
typedef struct {
    RSDK_OBJECT
} ObjectFXFade;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 speedIn;
    int32 wait;
    int32 speedOut;
    uint32 color;
    bool32 oneWay;
    bool32 eventOnly;
    bool32 overHUD;
    bool32 fadeOutBlack;
#if MANIA_USE_PLUS
    bool32 transitionScene;
#endif
} EntityFXFade;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Entity *parent;
    StateMachine(state);
    int32 timer;
    Vector2 startPos;
    int32 promptID;
    int32 buttonID;
    uint8 headingAnchor;
    int32 unused;
    int32 prevPrompt;
    int32 prevButton;
    int32 mappings;
    bool32 textVisible;
    int32 scaleMax;
    int32 scaleSpeed;
    bool32 disableScale;
    Vector2 touchSize;
    Vector2 touchPos;
    bool32 touched;
    Animator decorAnimator;
    Animator buttonAnimator;
    Animator promptAnimator;
    uint16 textSprite;
} EntityUIButtonPrompt;

// Entity Class
typedef struct {
    MANIA_UI_ITEM_BASE
    int32 unused;
    LeaderboardEntry *leaderboardEntry;
    String unusedText[5];
    String rankText[5];
    String nameText[5];
    int32 times[5];
    int32 ranks[5];
    bool32 isUser[5];
    uint8 characterID;
    uint8 zoneID;
    uint8 actID;
    int32 zoneIconSprX;
    uint8 fuzzDir;
    bool32 lostFocus;
    int32 entryOffset;
    int32 entryLength;
#if !MANIA_USE_PLUS
    bool32 viewingUserRank;
    int32 taRecord;
#endif
    bool32 yPressCBEnabled;
    StateMachine(yPressCB);
    String zoneName;
    Animator unusedAnimator1;
    Animator unusedAnimator2;
    Animator zoneIconAnimator;
    Animator zoneNameAnimator;
    Animator textAnimator;
    Animator fuzzAnimator;
    Animator playerAnimator;
    Animator playerShadowAnimator;
    Animator playerNameAnimator;
    Animator actNumAnimator;
    Animator taAnimator;
    Animator timeAnimator;
    uint16 textFrames;
} EntityUILeaderboard;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator unusedAnimator;
    int32 unused1;
    int32 unused2;
    Vector2 size;
    String text;
    int32 width;
    Animator textAnimator;
} EntityUIInfoLabel;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);     // unused
    Animator unusedAnimator; // unused
    Vector2 *parentPos;
    Vector2 offset;
    Vector2 size;
    uint8 p1Score;
    uint8 p2Score;
    bool32 showWinner;
    uint8 winnerID;
    int32 bgEdgeSize;
    String scoreText;
    Animator totalAnimator;
    Animator textAnimator;
    Animator winnerAnimator;
    Animator winsAnimator;
    uint16 textFrames;
} EntityUIVsScoreboard;

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 unused1;
    bool32 initializedMenuReturn;
    bool32 initializedMenu;
    bool32 initializedAPI;
    bool32 initializedSaves;
    int32 unused2;
    int32 unused3;
    EntityFXFade *fxFade;
#if !MANIA_USE_PLUS
    EntityUIButtonPrompt *delSavePrompt;
    EntityUIControl *mainMenu;
    EntityUIControl *timeAttack;
    EntityUIControl *timeAttackZones;
    EntityUIControl *leaderboards;
    EntityUILeaderboard *leaderboardWidget;
    EntityUIButtonPrompt *leaderboardPrompt;
    EntityUIControl *competition;
    EntityUIControl *competitionRules;
    EntityUIControl *competitionZones;
    EntityUIControl *competitionRound;
    EntityUIInfoLabel *roundLabel;
    EntityUIVsScoreboard *roundScoreboard;
    EntityUIControl *competitionTotal;
    EntityUIInfoLabel *totalLabel;
    EntityUIVsScoreboard *totalScoreboard;
    EntityUIControl *saveSelect;
    EntityUIControl *noSaveMode;
    EntityUIControl *secrets;
    EntityUIControl *extras;
    EntityUIControl *options;
    EntityUIButtonPrompt *optionsPrompt;
    EntityUIControl *video;
    EntityUIControl *video_win;
    EntityUIControl *sound;
    EntityUIControl *controls_win;
    EntityUIControl *controls_KB;
    EntityUIControl *controls_PS4;
    EntityUIControl *controls_XB1;
    EntityUIControl *controls_NX;
    EntityUIControl *controls_NX_Grip;
    EntityUIControl *controls_NX_JoyCon;
    EntityUIControl *controls_NX_Pro;
    EntityUIControl *language;
    int32 unused4;
    int32 unused5;
    int32 vsTotalTimer;
    int32 unused6;
    EntityUIDialog *connectingDlg;
#endif
} ObjectMenuSetup;

#if MANIA_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    EntityUIControl *extrasControl;
    int32 cheatCode[8];
} ObjectExtrasMenu;
#endif

extern EntityUIDialog *(*UIDialog_CreateDialogOk)(String *text, void (*callback)(void), bool32 closeOnSelect);
extern EntityUIDialog *(*UIDialog_CreateDialogYesNo)(String *text, void (*callbackYes)(void), void (*callbackNo)(void), bool32 closeOnSelect_Yes,
                                                     bool32 closeOnSelect_No);
extern void (*UIDialog_CloseOnSel_HandleSelection)(EntityUIDialog *dialog, void (*callback)(void));

extern void (*UIControl_ClearInputs)(uint8 buttonID);

#if MANIA_USE_PLUS
extern int32 (*CompetitionMenu_HandleUnlocks)(void);
extern void (*ExtrasMenu_HandleUnlocks)(void);
extern void (*MainMenu_HandleUnlocks)(void);
extern void (*ManiaModeMenu_HandleUnlocks)(void);
extern void (*OptionsMenu_HandleUnlocks)(void);
extern void (*TimeAttackMenu_HandleUnlocks)(void);
extern void (*UISubHeading_HandleUnlocks)(void);
#else
extern void (*MenuSetup_HandleUnlocks)(void);
#endif

#endif