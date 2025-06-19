#ifndef OBJ_BUBBLER_H
#define OBJ_BUBBLER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxRange;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
} ObjectBubbler;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int16 timer;
    uint16 spawnTimer;
    Vector2 startPos;
    uint8 startDir;
    Animator bodyHitbox;
    Animator flameAnimator;
} EntityBubbler;

// Object Entity
extern ObjectBubbler *Bubbler;

// Standard Entity Events
void Bubbler_StageLoad(void);

#endif //! OBJ_BUBBLER_H
