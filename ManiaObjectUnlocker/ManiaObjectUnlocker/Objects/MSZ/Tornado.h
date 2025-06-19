#ifndef OBJ_TORNADO_H
#define OBJ_TORNADO_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    TABLE(int32 flameOffsets[5], { -0x20000, -0x10000, 0, 0x10000, 0x20000 });
    uint16 aniFrames;
    uint16 knuxFrames;
    uint16 sfxExplosion;
    uint16 sfxImpact;
} ObjectTornado;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 collideTimer;
    int32 timer;
    int32 turnAngle;
    int32 mode;
    bool32 isStood;
    bool32 showFlame;
    int32 storeY;
    int32 gravityForce;
    int32 prevPosY;
    int32 moveVelocityY;
    Vector2 movePos;
    Vector2 knuxPos;
    Vector2 knuxVel;
    int32 offsetX;
    Animator animatorTornado;
    Animator animatorPropeller;
    Animator animatorPilot;
    Animator animatorFlame;
    Animator animatorKnux;
} EntityTornado;

// Object Struct
extern ObjectTornado *Tornado;

// Standard Entity Events
void Tornado_StageLoad(void);

#endif //! OBJ_TORNADO_H
