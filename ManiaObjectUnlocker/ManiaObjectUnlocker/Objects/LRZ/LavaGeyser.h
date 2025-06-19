#ifndef OBJ_LAVAGEYSER_H
#define OBJ_LAVAGEYSER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxHit;
    uint16 sfxExplosion;
    uint16 sfxDrill;
    uint16 sfxLavaGeyser;
} ObjectLavaGeyser;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    Animator plumeAnimator;
    Animator flowAnimator;
    Animator plumeLoopAnimator;
    int32 startingHeight;
    int32 height;
    int32 timer;
    uint16 unused;
    uint16 interval;
    uint16 intervalOffset;
    uint16 duration;
    int32 force;
} EntityLavaGeyser;

// Object Struct
extern ObjectLavaGeyser *LavaGeyser;

// Standard Entity Events
void LavaGeyser_StageLoad(void);

#endif //! OBJ_LAVAGEYSER_H
