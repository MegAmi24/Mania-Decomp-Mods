#ifndef OBJ_BATBRAIN_H
#define OBJ_BATBRAIN_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    uint16 aniFrames;
    uint16 sfxFlap;
} ObjectBatbrain;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 targetY;
    void *target;
    Vector2 startPos;
    Animator animator;
} EntityBatbrain;

// Object Struct
extern ObjectBatbrain *Batbrain;

// Standard Entity Events
void Batbrain_StageLoad(void);

#endif //! OBJ_BATBRAIN_H
