#ifndef OBJ_NEWTRON_H
#define OBJ_NEWTRON_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxShoot;
    Hitbox hitboxFly; // not sure why isn't this used in this object... GHZ/CheckerBall uses it though
    Hitbox hitboxProjectile;
    Hitbox hitboxRange;
    uint16 aniFrames;
} ObjectNewtron;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    int32 timer;
    Vector2 startPos;
    Animator animator;
    Animator flameAnimator;
} EntityNewtron;

// Object Struct
extern ObjectNewtron *Newtron;

// Standard Entity Events
void Newtron_StageLoad(void);

#endif //! OBJ_NEWTRON_H
