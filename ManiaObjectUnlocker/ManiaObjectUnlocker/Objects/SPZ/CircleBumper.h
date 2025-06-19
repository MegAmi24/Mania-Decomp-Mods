#ifndef OBJ_CIRCLEBUMPER_H
#define OBJ_CIRCLEBUMPER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBumper;
    uint16 aniFrames;
    uint16 sfxBumper;
} ObjectCircleBumper;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(stateCollide);
    StateMachine(stateMove);
    int32 hitCount;
    int32 type;
    Vector2 amplitude;
    int32 speed;
    Vector2 drawPos;
    Animator animator;
    int32 unused;
} EntityCircleBumper;

// Object Struct
extern ObjectCircleBumper *CircleBumper;

// Standard Entity Events
void CircleBumper_StageLoad(void);

#endif //! OBJ_CIRCLEBUMPER_H
