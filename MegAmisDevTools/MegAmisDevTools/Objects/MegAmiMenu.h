#ifndef OBJ_MEGAMIMENU_H
#define OBJ_MEGAMIMENU_H

#include "GameAPI/Game.h"
#include "Player.h"
#include "Misc.h"

#define API_GetConfirmButtonFlip API.GetConfirmButtonFlip

#define MAINBOX_XPOS   16
#define MAINBOX_WIDTH  150
#define SUBBOX_XPOS    MAINBOX_XPOS + MAINBOX_WIDTH + 3
#define BOX_YPOS       12
#define OPTION_SPACING 14
#define BOX_HEIGHT(x)  ((x)*OPTION_SPACING) + 5 // x = Option Count

typedef enum {
    MEGAMIMENU_P1CHAR,
    MEGAMIMENU_P2CHAR,
    MEGAMIMENU_SHIELD,
    MEGAMIMENU_SHOES,
    MEGAMIMENU_HYPERRING,
    MEGAMIMENU_SETRINGS,
    MEGAMIMENU_SUPER,
    MEGAMIMENU_INV,
    MEGAMIMENU_EXIT,
    MEGAMIMENU_COUNT,
} MegAmiMenuOptions;

// Object Class
typedef struct {
    RSDK_OBJECT
    bool32 playerInv[PLAYER_COUNT];
    uint16 aniFrames;
    uint16 sfxFail;
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
    String p1char;
    String p2char;
    String shield;
    String shoes;
    String hyperRing;
    String setRings;
    String super;
    String inv;
    String exit;
    String sonic;
    String tails;
    String knux;
#if MANIA_USE_PLUS
    String mighty;
    String ray;
#endif
    String none;
    String blue;
    String bubble;
    String fire;
    String lightning;
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
#if RETRO_INCLUDE_EDITOR
void MegAmiMenu_EditorDraw(void);
void MegAmiMenu_EditorLoad(void);
#endif
void MegAmiMenu_Serialize(void);

// Extra Entity Functions
void MegAmiMenu_State_Main(void);
void MegAmiMenu_State_P1Char(void);
void MegAmiMenu_State_P2Char(void);
void MegAmiMenu_State_Shield(void);
void MegAmiMenu_State_SetRings(void);

void MegAmiMenu_State_DrawChar(void);
void MegAmiMenu_State_DrawShield(void);
void MegAmiMenu_State_DrawSetValue(void);

#endif //! OBJ_MEGAMIMENU_H
