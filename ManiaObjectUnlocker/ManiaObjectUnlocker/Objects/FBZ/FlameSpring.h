#ifndef OBJ_FLAMESPRING_H
#define OBJ_FLAMESPRING_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxSpring;
    Hitbox hitboxFlame;
    uint16 sfxSpring;
    uint16 sfxFlame;
} ObjectFlameSpring;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 type;
    int32 force;
    uint8 playerAni;
    uint8 offset;
    Vector2 flamePosL;
    Vector2 flamePosR;
    bool32 spittingFire;
    uint8 timer;
    Animator mainAnimator;
    Animator nozzleAnimator;
} EntityFlameSpring;

// Object Struct
extern ObjectFlameSpring *FlameSpring;

// Standard Entity Events
void FlameSpring_StageLoad(void);

#endif //! OBJ_FLAMESPRING_H
