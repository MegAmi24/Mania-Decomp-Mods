#ifndef OBJ_PUSHSPRING_H
#define OBJ_PUSHSPRING_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxPush;
    uint16 sfxSpring;
} ObjectPushSpring;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    StateMachine(stateCollide);
    uint8 type;
    int32 pushOffset;
    int32 timer;
    Hitbox hitbox;
    bool32 beingPushed;
    Animator animator;
} EntityPushSpring;

// Object Struct
extern ObjectPushSpring *PushSpring;

// Standard Entity Events
void PushSpring_StageLoad(void);

#endif //! OBJ_PUSHSPRING_H
