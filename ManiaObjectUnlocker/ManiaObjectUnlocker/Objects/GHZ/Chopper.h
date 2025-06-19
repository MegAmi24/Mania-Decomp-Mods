#ifndef OBJ_CHOPPER_H
#define OBJ_CHOPPER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxJump;
    Hitbox hitboxSwim;
    Hitbox hitboxRange;
    Hitbox hitboxWater;
    uint16 aniFrames;
} ObjectChopper;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    uint16 timer;
    bool32 charge;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
} EntityChopper;

// Object Struct
extern ObjectChopper *Chopper;

// Standard Entity Events
void Chopper_StageLoad(void);

#endif //! OBJ_CHOPPER_H
