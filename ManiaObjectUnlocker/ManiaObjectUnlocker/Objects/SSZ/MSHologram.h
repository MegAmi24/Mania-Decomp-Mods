#ifndef OBJ_MSHOLOGRAM_H
#define OBJ_MSHOLOGRAM_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitbox;
    uint16 sfxExplosion;
} ObjectMSHologram;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    bool32 destroyed;
    Animator projectorAnimator;
    Animator lightsAnimator;
    Animator metalSonicAnimator;
    Animator rabbitAnimator;
    Animator canaryAnimator;
} EntityMSHologram;

// Object Struct
extern ObjectMSHologram *MSHologram;

// Standard Entity Events
void MSHologram_StageLoad(void);

#endif //! OBJ_MSHOLOGRAM_H
