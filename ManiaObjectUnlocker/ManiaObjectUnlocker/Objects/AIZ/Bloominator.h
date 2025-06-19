#ifndef OBJ_BLOOMINATOR_H
#define OBJ_BLOOMINATOR_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
    uint16 sfxShot;
} ObjectBloominator;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    Animator animator;
} EntityBloominator;

// Object Struct
extern ObjectBloominator *Bloominator;

// Standard Entity Events
void Bloominator_StageLoad(void);
#endif

#endif //! OBJ_BLOOMINATOR_H
