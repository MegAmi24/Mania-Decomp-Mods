#ifndef OBJ_DEBRIS_H
#define OBJ_DEBRIS_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
} ObjectDebris;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 gravityStrength;
    int32 rotSpeed;
    Vector2 scaleSpeed;
    int32 delay;
    Animator animator;
} EntityDebris;

// Object Struct
extern ObjectDebris *Debris;

void (*Debris_State_Fall)(void);

#endif //! OBJ_DEBRIS_H
