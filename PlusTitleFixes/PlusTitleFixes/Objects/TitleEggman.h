#ifndef OBJ_TITLEEGGMAN_H
#define OBJ_TITLEEGGMAN_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectTitleEggman;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    Vector2 originPos;
    Animator smokeAnimator;
    Animator eggmanAnimator;
    Animator chainAnimator;
    Animator capsuleAnimator;
} EntityTitleEggman;
#endif

#endif //! OBJ_TITLEEGGMAN_H
