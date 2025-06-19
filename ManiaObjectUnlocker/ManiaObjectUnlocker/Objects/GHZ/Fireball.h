#ifndef OBJ_FIREBALL_H
#define OBJ_FIREBALL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxFireball;
    uint16 sfxFireball;
} ObjectFireball;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    Animator animator;
    uint8 type;
    uint8 interval;
    uint8 intervalOffset;
    int32 unused1;
    int32 unused2;
} EntityFireball;

// Object Entity
extern ObjectFireball *Fireball;

// Standard Entity Events
void Fireball_StageLoad(void);

#endif //! OBJ_FIREBALL_H
