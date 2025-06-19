#ifndef OBJ_CRABMEAT_H
#define OBJ_CRABMEAT_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
} ObjectCrabmeat;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    uint8 shootState;
    Vector2 startPos;
    int32 startDir;
    Animator animator;
} EntityCrabmeat;

// Object Struct
extern ObjectCrabmeat *Crabmeat;

// Standard Entity Events
void Crabmeat_StageLoad(void);

#endif //! OBJ_CRABMEAT_H
