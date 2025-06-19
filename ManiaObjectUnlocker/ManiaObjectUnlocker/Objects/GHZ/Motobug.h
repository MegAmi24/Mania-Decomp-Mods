#ifndef OBJ_MOTOBUG_H
#define OBJ_MOTOBUG_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    uint16 aniFrames;
} ObjectMotobug;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 turnTimer;
    int32 timer;
    Vector2 startPos;
    uint8 startDir;
    bool32 wasTurning;
    Animator animator;
} EntityMotobug;

// Object Struct
extern ObjectMotobug *Motobug;

// Standard Entity Events
void Motobug_StageLoad(void);

#endif //! OBJ_MOTOBUG_H
