#ifndef OBJ_WALKERLEGS_H
#define OBJ_WALKERLEGS_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
    uint16 particleFrames;
    uint16 sfxWalkerLegs;
    uint16 sfxWalkerLegs2;
    Animator legAnimator;
    Animator linkAnimator;
    bool32 hasAchievement;
} ObjectWalkerLegs;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint16 steps;
    int32 activePlayers[2];
    Vector2 startPos;
    Vector2 legPos[2];
    Vector2 legCollisionOffset[2];
    Vector2 prevLegPos[2];
    int32 smokeSpawnY[2];
    int32 startAngle;
    int32 activeLeg;
    bool32 finishedStep;
    int32 angleVel;
    uint16 stepCount;
    int32 smokeSpawnTimer[2];
    int32 timer;
} EntityWalkerLegs;

// Object Struct
extern ObjectWalkerLegs *WalkerLegs;

// Standard Entity Events
void WalkerLegs_StageLoad(void);

#endif //! OBJ_WALKERLEGS_H
