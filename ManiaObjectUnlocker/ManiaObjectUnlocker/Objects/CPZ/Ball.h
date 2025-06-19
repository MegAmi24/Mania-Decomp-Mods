#ifndef OBJ_BALL_H
#define OBJ_BALL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBall;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxSplash;
} ObjectBall;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    void *targetPlayer;
    Vector2 startPos;
    Animator animator;
} EntityBall;

// Object Entity
extern ObjectBall *Ball;

// Standard Entity Events
void Ball_StageLoad(void);

#endif //! OBJ_BALL_H
