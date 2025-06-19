#ifndef OBJ_OCTUS_H
#define OBJ_OCTUS_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxProjectile;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxShot;
} ObjectOctus;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    uint8 unused1;
    Vector2 startPos;
    uint8 startDir;
    int32 unused2;
    Animator animator;
} EntityOctus;

// Object Struct
extern ObjectOctus *Octus;

// Standard Entity Events
void Octus_StageLoad(void);

#endif //! OBJ_OCTUS_H
