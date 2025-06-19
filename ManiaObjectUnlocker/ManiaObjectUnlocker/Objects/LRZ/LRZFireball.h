#ifndef OBJ_LRZFIREBALL_H
#define OBJ_LRZFIREBALL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxFireball;
    uint16 sfxFireball;
} ObjectLRZFireball;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    Animator animator;
    uint8 type;
    uint16 interval;
    uint16 intervalOffset;
    int32 unused1;
    int32 unused2;
    int32 unused3;
} EntityLRZFireball;

// Object Struct
extern ObjectLRZFireball *LRZFireball;

// Standard Entity Events
void LRZFireball_StageLoad(void);

#endif //! OBJ_LRZFIREBALL_H
