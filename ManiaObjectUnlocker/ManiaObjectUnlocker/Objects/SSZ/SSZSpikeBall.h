#ifndef OBJ_SSZSPIKEBALL_H
#define OBJ_SSZSPIKEBALL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxPon;
    Hitbox hitboxSpikeBall;
    Hitbox hitboxBase[4];
} ObjectSSZSpikeBall;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    uint16 interval;
    uint16 intervalOffset;
    int32 speed;
    int32 dist;
    uint8 timer;
    Vector2 spikeBallPos;
    Animator baseAnimator;
    Animator spikeBallAnimator;
} EntitySSZSpikeBall;

// Object Struct
extern ObjectSSZSpikeBall *SSZSpikeBall;

// Standard Entity Events
void SSZSpikeBall_StageLoad(void);

#endif //! OBJ_SSZSPIKEBALL_H
