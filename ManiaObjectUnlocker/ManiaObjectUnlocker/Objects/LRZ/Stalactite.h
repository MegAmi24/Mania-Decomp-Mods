#ifndef OBJ_STALACTITE_H
#define OBJ_STALACTITE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxStalactite;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxShoot;
} ObjectStalactite;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Animator animator;
} EntityStalactite;

// Object Struct
extern ObjectStalactite *Stalactite;

// Standard Entity Events
void Stalactite_StageLoad(void);

#endif //! OBJ_STALACTITE_H
