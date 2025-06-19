#ifndef OBJ_BLASTOID_H
#define OBJ_BLASTOID_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBody;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
    uint16 sfxShot;
} ObjectBlastoid;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 timer;
    Animator animator;
} EntityBlastoid;

// Object Struct
extern ObjectBlastoid *Blastoid;

// Standard Entity Events
void Blastoid_StageLoad(void);

#endif //! OBJ_BLASTOID_H
