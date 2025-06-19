#ifndef OBJ_LAUNCHSPRING_H
#define OBJ_LAUNCHSPRING_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    bool32 isTMZ;
    uint16 aniFrames;
    uint16 sfxGrab;
    uint16 sfxClack;
    uint16 sfxSpeedBooster;
} ObjectLaunchSpring;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Animator mainAnimator;
    Animator jointAnimator;
    Animator springAnimator;
    uint8 type;
    uint8 rotDir;
    uint8 rotSpeed;
    bool32 manual;
    bool32 strict;
    uint8 timer;
    uint8 springPivot;
    uint8 autoFireTimer;
    int16 minAngle;
    int16 maxAngle;
    void *playerPtr;
} EntityLaunchSpring;

// Object Struct
extern ObjectLaunchSpring *LaunchSpring;

// Standard Entity Events
void LaunchSpring_StageLoad(void);

#endif //! OBJ_LAUNCHSPRING_H
