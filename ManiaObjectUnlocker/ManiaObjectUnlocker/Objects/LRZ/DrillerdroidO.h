#ifndef OBJ_DRILLERDROIDO_H
#define OBJ_DRILLERDROIDO_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxCore;
    Hitbox hitboxPistonL;
    Hitbox hitboxPistonR;
    Hitbox hitboxDrillL;
    Hitbox hitboxDrillR;
    Hitbox hitboxLandPosSegmentBreak;
    Hitbox hitboxLandPosR;
    Hitbox hitboxLandPosL;
    Hitbox hitboxEmitterRange;
    int32 pistonPos[2];
    int32 drillPos[2];
    int32 pistonDelay[2];
    int32 drillDelay[2];
    int32 pistonMoveDir[2];
    int32 drillMoveDir[2];
    uint8 drillSfxTimer;
    bool32 playingDrillSfx;
    uint8 canBreakSegment;
    int32 childSlotStart;
    uint8 currentLevel;
    bool32 emitFireballs;
    void *boss;
    uint16 aniFrames;
    uint16 ticFrames;
    uint16 sfxHit;
    uint16 sfxExplosion;
    uint16 sfxDrill;
    uint16 sfxImpact;
    uint16 sfxJump;
    uint16 sfxTargeting;
    uint16 sfxSizzle;
} ObjectDrillerdroidO;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 type;
    StateMachine(state);
    StateMachine(stateDraw);
    Animator mainAnimator;
    Animator armorAnimator;
    Animator targetLockAnimator;
    void *target;
    Vector2 targetEdgeOffset;
    int32 startY;
    int32 timer;
    uint8 invincibilityTimer;
    int8 health;
} EntityDrillerdroidO;

// Object Struct
extern ObjectDrillerdroidO *DrillerdroidO;

// Standard Entity Events
void DrillerdroidO_StageLoad(void);

#endif //! OBJ_DRILLERDROIDO_H
