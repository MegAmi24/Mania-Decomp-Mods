#ifndef OBJ_ROCKDRILL_H
#define OBJ_ROCKDRILL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBody;
    Hitbox hitboxPistonL;
    Hitbox hitboxPistonR;
    Hitbox hitboxDrills;
    uint8 drillSfxTimer;
    bool32 playingDrillSfx;
    uint16 aniFrames;
    uint16 sfxHit;
    uint16 sfxExplosion;
    uint16 sfxDrill;
} ObjectRockDrill;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Animator animator;
    bool32 lockCamera;
    int32 boundsL;
    int32 boundsR;
    int32 boundsT;
    int32 boundsB;
    int32 timer;
    int32 pistonPos[2];
    int32 drillPos[2];
    int32 pistonDelay[2];
    int32 drillDelay[2];
    int32 pistonMoveDir[2];
    int32 drillMoveDir[2];
    uint8 invincibilityTimer;
} EntityRockDrill;

// Object Struct
extern ObjectRockDrill *RockDrill;

// Standard Entity Events
void RockDrill_StageLoad(void);

#endif //! OBJ_ROCKDRILL_H
