#ifndef OBJ_IWAMODOKI_H
#define OBJ_IWAMODOKI_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxRange;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
} ObjectIwamodoki;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    bool32 lrzConvPhys;
    Vector2 startPos;
    Vector2 moveOffset;
    Vector2 preMovePos;
    Vector2 postMovePos;
    uint8 startDir;
    int32 timer;
    int32 chargeCount;
    Animator animator;
} EntityIwamodoki;

// Object Struct
extern ObjectIwamodoki *Iwamodoki;

// Standard Entity Events
void Iwamodoki_StageLoad(void);

#endif //! OBJ_IWAMODOKI_H
