#ifndef OBJ_MISC_H
#define OBJ_MISC_H

#include "GameAPI/Game.h"
#include "UISaveSlot.h"

#define UICONTROL_BUTTON_COUNT (64)
#if MANIA_USE_PLUS
#define UICONTROL_PROMPT_COUNT (4)
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

#endif