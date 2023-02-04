#ifndef OBJ_TITLELOGO_H
#define OBJ_TITLELOGO_H

#include "GameAPI/Game.h"

typedef enum {
    TITLELOGO_EMBLEM,
    TITLELOGO_RIBBON,
    TITLELOGO_GAMETITLE,
    TITLELOGO_POWERLED,
    TITLELOGO_COPYRIGHT,
    TITLELOGO_RINGBOTTOM,
    TITLELOGO_PRESSSTART,
#if MANIA_USE_PLUS
    TITLELOGO_PLUS,
#endif
} TitleLogoTypes;

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
#if MANIA_USE_PLUS
    uint16 plusFrames;
    uint16 sfxPlus;
#endif
} ObjectTitleLogo;

// Entity Class
typedef struct {
    RSDK_ENTITY
    int32 type;
#if MANIA_USE_PLUS
    StateMachine(state);
#endif
    bool32 showRibbonCenter;
    int32 timer;
    int32 storeY;
    Animator mainAnimator;
#if MANIA_USE_PLUS
    Animator plusAnimator;
#endif
    Animator ribbonCenterAnimator;
} EntityTitleLogo;

extern void (*TitleLogo_SetupPressStart)(void);
extern StateMachine(TitleLogo_State_HandleSetup);

#endif //! OBJ_TITLELOGO_H
