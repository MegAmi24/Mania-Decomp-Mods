#ifndef OBJ_RHINOBOT_H
#define OBJ_RHINOBOT_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    uint16 aniFrames;
    uint16 sfxHuff;
} ObjectRhinobot;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDelay);
    int32 unused1;
    int32 timer;
    int32 skidDir;
    int32 moveDir;
    bool32 drawDust;
    int32 acceleration;
    int32 topSpeed;
    Vector2 startPos;
    uint8 startDir;
    Animator bodyAnimator;
    Animator dustAnimator;
} EntityRhinobot;

// Object Struct
extern ObjectRhinobot *Rhinobot;

// Standard Entity Events
void Rhinobot_StageLoad(void);

#endif

#endif //! OBJ_RHINOBOT_H
