#ifndef OBJ_TITLESETUP_H
#define OBJ_TITLESETUP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    bool32 useAltIntroMusic;
    uint16 aniFrames;
    uint16 sfxMenuBleep;
    uint16 sfxMenuAccept;
    uint16 sfxRing;
#if MANIA_USE_PLUS
    uint8 cheatCode[8];
#endif
} ObjectTitleSetup;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 timer;
    Vector2 drawPos;
    int32 touched;
    Animator animator;
} EntityTitleSetup;

// Object Struct
extern ObjectTitleSetup *TitleSetup;

// Extra Entity Functions
#if MANIA_USE_PLUS
extern void (*TitleSetup_CheckCheatCode)(void);
#endif

extern StateMachine(TitleSetup_State_WaitForSonic);
extern StateMachine(TitleSetup_State_SetupLogo);
#if MANIA_USE_PLUS
extern StateMachine(TitleSetup_State_SetupPlusLogo);
extern StateMachine(TitleSetup_State_WaitForEnter);
#endif

#if MANIA_USE_PLUS
bool32 TitleSetup_State_SetupPlusLogo_Hook(bool32 skipped);
#endif

#endif //! OBJ_TITLESETUP_H
