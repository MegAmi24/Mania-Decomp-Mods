#ifndef OBJ_SWEEP_H
#define OBJ_SWEEP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxRange;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
    uint16 sfxPon;
} ObjectSweep;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateStore);
    int32 timer;
    uint8 hasShot;
    Vector2 startPos;
    uint8 startDir;
    void *water;
    Animator animator;
} EntitySweep;

// Object Struct
extern ObjectSweep *Sweep;

// Standard Entity Events
void Sweep_StageLoad(void);

#endif //! OBJ_SWEEP_H
