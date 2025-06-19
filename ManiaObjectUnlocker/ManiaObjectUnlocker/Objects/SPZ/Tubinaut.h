#ifndef OBJ_TUBINAUT_H
#define OBJ_TUBINAUT_H

#include "GameAPI/Game.h"

#define TUBINAUT_ORB_COUNT (3)

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxFace;
    Hitbox hitboxOrb;
    Hitbox hitboxSpin;
    uint16 aniFrames;
    uint16 sfxPowerdown;
    uint16 sfxRepel;
} ObjectTubinaut;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(orbState);
    Animator bodyAnimator;
    Animator fieldAnimator;
    Vector2 startPos;
    Vector2 orbPositions[TUBINAUT_ORB_COUNT];
    int32 orbAngles[TUBINAUT_ORB_COUNT];
    int16 reAdjustTimers[TUBINAUT_ORB_COUNT];
    bool32 ballsVisible[TUBINAUT_ORB_COUNT]; // hehe
    Animator ballAnimators[TUBINAUT_ORB_COUNT];
    uint16 playerTimers[PLAYER_COUNT];
    int32 attackTimer;
    uint16 activeOrbs;
    uint8 orbCount;
    int32 timer;
    uint16 distanceRemain;
    uint16 distance;
} EntityTubinaut;

// Object Struct
extern ObjectTubinaut *Tubinaut;

// Standard Entity Events
void Tubinaut_StageLoad(void);

#endif //! OBJ_TUBINAUT_H
