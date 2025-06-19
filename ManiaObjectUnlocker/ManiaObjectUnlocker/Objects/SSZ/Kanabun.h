#ifndef OBJ_KANABUN_H
#define OBJ_KANABUN_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    uint16 aniFrames;
} ObjectKanabun;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 unused;
    Vector2 startPos;
    uint8 startDir;
    int32 hVel;
    uint8 hDist;
    uint8 bobDist;
    uint8 angleVel;
    Animator animator;
} EntityKanabun;

// Object Struct
extern ObjectKanabun *Kanabun;

// Standard Entity Events
void Kanabun_StageLoad(void);

#endif //! OBJ_KANABUN_H
