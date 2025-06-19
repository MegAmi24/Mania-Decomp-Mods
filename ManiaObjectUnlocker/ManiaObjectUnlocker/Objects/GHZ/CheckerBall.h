#ifndef OBJ_CHECKERBALL_H
#define OBJ_CHECKERBALL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBall;
    Hitbox innerBox;
    Hitbox outerBox;
    uint8 heightArray[24];
    uint8 unusedArray[24];
    uint16 aniFrames;
} ObjectCheckerBall;

// Entity Class
typedef struct {
    RSDK_ENTITY
    bool32 playerControlled;
    int32 angleVel;
    int32 ballAngle;
    Vector2 roundedPos;
    Vector2 collisionOffset;
    uint8 activePlayers;
    Animator animator;
} EntityCheckerBall;

// Object Struct
extern ObjectCheckerBall *CheckerBall;

// Standard Entity Events
void CheckerBall_StageLoad(void);

#endif //! OBJ_CHECKERBALL_H
