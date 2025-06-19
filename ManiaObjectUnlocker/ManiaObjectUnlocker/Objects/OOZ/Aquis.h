#ifndef OBJ_AQUIS_H
#define OBJ_AQUIS_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxRange;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
    uint16 sfxShot;
} ObjectAquis;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    uint8 playerInRange;
    int32 remainingTurns;
    Vector2 startPos;
    uint8 startDir;
    Animator mainAnimator;
    Animator wingAnimator;
} EntityAquis;

// Object Struct
extern ObjectAquis *Aquis;

// Standard Entity Events
void Aquis_StageLoad(void);

#endif //! OBJ_AQUIS_H
