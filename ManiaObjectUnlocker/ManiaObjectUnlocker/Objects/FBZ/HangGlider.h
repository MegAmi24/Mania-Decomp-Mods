#ifndef OBJ_HANGGLIDER_H
#define OBJ_HANGGLIDER_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxUnused;
    uint16 aniFrames;
} ObjectHangGlider;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 unused1;
    int32 gravityStrength;
    int32 unused2;
    int32 unused3;
    void *attachedPlayer;
    Animator sailAnimator;
    Animator handleBackAnimator;
    Animator handleFrontAnimator;
    Animator playerAnimator;
} EntityHangGlider;

// Object Struct
extern ObjectHangGlider *HangGlider;

// Standard Entity Events
void HangGlider_StageLoad(void);

#endif

#endif //! OBJ_HANGGLIDER_H
