#ifndef OBJ_POHBEE_H
#define OBJ_POHBEE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
} ObjectPohBee;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    int32 chainPos[2];
    int32 chainAngle[2];
    int32 unused;
    bool32 isTurning;
    Animator bodyAnimator;
    Animator wingsAnimator;
    Animator chainAnimator;
    Animator spikeAnimator;
    Hitbox hitboxes[2];
    uint8 spikeCount;
    Vector2 amplitude;
    ManiaPlaneFilterTypes planeFilter;
} EntityPohBee;

// Object Struct
extern ObjectPohBee *PohBee;

// Standard Entity Events
void PohBee_StageLoad(void);

#endif //! OBJ_POHBEE_H
