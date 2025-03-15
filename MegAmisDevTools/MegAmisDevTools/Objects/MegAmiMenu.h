#ifndef OBJ_MEGAMIMENU_H
#define OBJ_MEGAMIMENU_H

#include "GameAPI/Game.h"
#include "Player.h"
#include "Misc.h"

#if MANIA_USE_PLUS
#define API_GetConfirmButtonFlip API.GetConfirmButtonFlip
#else
#define API_GetConfirmButtonFlip APICallback_GetConfirmButtonFlip
#endif

#define MAINBOX_XPOS   (16)
#define SUBBOX_XPOS    (MAINBOX_XPOS + self->mainBoxWidth + 3)
#define BOX_YPOS       (12)
#define OPTION_SPACING (14)
#define BOX_HEIGHT(x)  ((x) * OPTION_SPACING + 5) // x = Option Count
#define BOX_COLOR      (0xFF0000)

#define selectedOption (self->menuOptions[self->mainSelection])

#define AddMenuOption(option, string)                                                                                                                \
    self->menuCount++;                                                                                                                               \
    self->menuOptions[self->menuCount] = option;                                                                                                     \
    RSDK.InitString(&self->menuStrings[self->menuCount], string, false);

#if MANIA_USE_PLUS
#define SetCharacterFlags()                                                                                                                          \
    globals->characterFlags = 0;                                                                                                                     \
    if (GET_CHARACTER_ID(1))                                                                                                                         \
        globals->characterFlags |= 1 << HUD_CharacterIndexFromID(GET_CHARACTER_ID(1));                                                               \
    if (GET_CHARACTER_ID(2))                                                                                                                         \
        globals->characterFlags |= 1 << HUD_CharacterIndexFromID(GET_CHARACTER_ID(2));                                                               \
    if (GET_STOCK_ID(1))                                                                                                                             \
        globals->characterFlags |= 1 << HUD_CharacterIndexFromID(GET_STOCK_ID(1));                                                                   \
    if (GET_STOCK_ID(2))                                                                                                                             \
        globals->characterFlags |= 1 << HUD_CharacterIndexFromID(GET_STOCK_ID(2));                                                                   \
    if (GET_STOCK_ID(3))                                                                                                                             \
        globals->characterFlags |= 1 << HUD_CharacterIndexFromID(GET_STOCK_ID(3));
#endif

#define DrawOptionText(string)                                                                                                                       \
    RSDK.DrawText(&self->animator, &drawPos, string, 0, string.length, ALIGN_LEFT, 0, 0, 0, true);                                                   \
    drawPos.y += TO_FIXED(OPTION_SPACING);

#define confirmPress                                                                                                                                 \
    (ControllerInfo[player->controllerID].keyStart.press                                                                                             \
     || (API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyB.press : ControllerInfo[player->controllerID].keyA.press))
#define backPress (API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyA.press : ControllerInfo[player->controllerID].keyB.press)

#define Y_THIRD (ScreenInfo->size.y / 3)

typedef enum {
    MEGAMIMENU_P1CHAR,
    MEGAMIMENU_P2CHAR,
#if MANIA_USE_PLUS
    MEGAMIMENU_STOCK1,
    MEGAMIMENU_STOCK2,
    MEGAMIMENU_STOCK3,
#endif
    MEGAMIMENU_SHIELD,
    MEGAMIMENU_SHOES,
    MEGAMIMENU_SETRINGS,
    MEGAMIMENU_HYPERRING,
    MEGAMIMENU_SUPER,
    MEGAMIMENU_INVINCIBILITY,
    MEGAMIMENU_EXIT,
    MEGAMIMENU_COUNT,
} MegAmiMenuOptions;

typedef enum {
    CHARACTER_NONE,
    CHARACTER_SONIC,
    CHARACTER_TAILS,
    CHARACTER_KNUCKLES,
#if MANIA_USE_PLUS
    CHARACTER_MIGHTY,
    CHARACTER_RAY,
#endif
    CHARACTER_COUNT,
} CharacterStrings;

// Object Class
typedef struct {
    RSDK_OBJECT
    bool32 playerInv[PLAYER_COUNT];
    uint16 aniFrames;
    String charStrings[CHARACTER_COUNT];
    String shieldStrings[SHIELD_COUNT];
    uint8 touchUp;
    uint8 touchDown;
    uint8 touchLeft;
    uint8 touchRight;
    uint8 touchConfirm;
    uint8 touchBack;
} ObjectMegAmiMenu;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int8 mainSelection;
    int8 subSelection;
    int32 customValue;
    uint8 valueDigits;
    Entity *parent;
    int8 menuCount;
    int8 menuOptions[MEGAMIMENU_COUNT];
    String menuStrings[MEGAMIMENU_COUNT];
    int32 mainBoxWidth;
    Animator animator;
} EntityMegAmiMenu;

// Object Struct
extern ObjectMegAmiMenu *MegAmiMenu;

// Standard Entity Events
void MegAmiMenu_Update(void);
void MegAmiMenu_LateUpdate(void);
void MegAmiMenu_StaticUpdate(void);
void MegAmiMenu_Draw(void);
void MegAmiMenu_Create(void *data);
void MegAmiMenu_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void MegAmiMenu_EditorDraw(void);
void MegAmiMenu_EditorLoad(void);
#endif
void MegAmiMenu_Serialize(void);

// States
void MegAmiMenu_State_Main(void);
void MegAmiMenu_State_P1Char(void);
void MegAmiMenu_State_P2Char(void);
#if MANIA_USE_PLUS
void MegAmiMenu_State_EncoreStock(void);
#endif
void MegAmiMenu_State_Shield(void);
void MegAmiMenu_State_SetRings(void);

// Draw States
void MegAmiMenu_State_DrawChar(void);
void MegAmiMenu_State_DrawShield(void);
void MegAmiMenu_State_DrawSetValue(void);

// Extra Entity Functions
void MegAmiMenu_HandleTouchControls(void);
bool32 MegAmiMenu_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2);
void MegAmiMenu_HandleUpDown(RSDKControllerState controller, int8 maxCount);
void MegAmiMenu_HandleSetValue(RSDKControllerState controller, int32 minValue, int32 maxValue);

#if !MANIA_USE_PLUS
extern bool32 (*APICallback_GetConfirmButtonFlip)(void);
#endif

#endif //! OBJ_MEGAMIMENU_H
