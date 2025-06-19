#ifndef OBJ_DIVEEGGMAN_H
#define OBJ_DIVEEGGMAN_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox unusedHitbox1;
    Hitbox hitboxBomb;
    Hitbox hitboxEggman;
    void *screwMobile;
    uint16 diveFrames;
    uint16 aniFrames;
    uint16 sfxBigFan;
    uint16 sfxHit;
    uint16 sfxExplosion;
    uint16 sfxRockemSockem;
} ObjectDiveEggman;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 startY;
    int32 timer;
    int32 invincibilityTimer;
    uint8 health;
    Animator animator;
} EntityDiveEggman;

// Object Struct
extern ObjectDiveEggman *DiveEggman;

// Standard Entity Events
void DiveEggman_StageLoad(void);

#endif //! OBJ_DIVEEGGMAN_H
