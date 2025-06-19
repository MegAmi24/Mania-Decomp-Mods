#ifndef OBJ_BLASTER_H
#define OBJ_BLASTER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxRange;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
} ObjectBlaster;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint16 unused1;
    uint16 timer;
    uint16 attackTimer;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
} EntityBlaster;

// Object Struct
extern ObjectBlaster *Blaster;

// Standard Entity Events
void Blaster_StageLoad(void);

#endif //! OBJ_BLASTER_H
