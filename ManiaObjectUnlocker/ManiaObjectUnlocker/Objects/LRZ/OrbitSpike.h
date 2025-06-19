#ifndef OBJ_ORBITSPIKE_H
#define OBJ_ORBITSPIKE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
} ObjectOrbitSpike;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator animator;
    Vector2 amplitude;
    uint8 offset;
    Vector2 center;
} EntityOrbitSpike;

// Object Struct
extern ObjectOrbitSpike *OrbitSpike;

// Standard Entity Events
void OrbitSpike_StageLoad(void);

// Extra Entity Functions

#endif //! OBJ_ORBITSPIKE_H
