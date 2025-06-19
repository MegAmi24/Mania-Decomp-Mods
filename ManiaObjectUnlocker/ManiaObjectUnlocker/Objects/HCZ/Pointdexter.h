#ifndef OBJ_POINTDEXTER_H
#define OBJ_POINTDEXTER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
} ObjectPointdexter;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 timer;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
} EntityPointdexter;

// Object Struct
extern ObjectPointdexter *Pointdexter;

// Standard Entity Events
void Pointdexter_StageLoad(void);

#endif //! OBJ_POINTDEXTER_H
