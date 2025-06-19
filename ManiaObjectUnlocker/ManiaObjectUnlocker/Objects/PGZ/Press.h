#ifndef OBJ_PRESS_H
#define OBJ_PRESS_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitbox;
    uint16 sfxImpact;
    uint16 sfxPress;
#if MANIA_USE_PLUS
    bool32 canSuper;
#endif
} ObjectPress;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint16 size;
    uint32 speed;
    int32 offTop;
    int32 offBottom;
    int32 topOffset;
    uint32 threads;
    int32 height;
    int32 timerStart;
    int32 timer;
    Vector2 drawPos;
    uint16 threadSprY;
    uint8 stoodPlayersRoof;
    uint8 stoodPlayersFloor;
    Animator crusherAnimator;
    Animator threadAnimator;
    Animator bumperAnimator;
} EntityPress;

// Object Struct
extern ObjectPress *Press;

// Standard Entity Events
void Press_StageLoad(void);

#endif //! OBJ_PRESS_H
