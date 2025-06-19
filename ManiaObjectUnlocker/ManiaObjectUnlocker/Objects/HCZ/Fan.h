#ifndef OBJ_FAN_H
#define OBJ_FAN_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 activePlayers;
    uint8 unused;
    int32 minVelocity;
    Hitbox hitboxTop;
    Hitbox hitboxBottom;
    Hitbox hitboxSides;
    Hitbox playerHitbox;
    uint16 aniFrames;
    uint16 sfxFan;
    bool32 playingFanSfx;
} ObjectFan;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateActivate);
    StateMachine(stateDeactivate);
    uint8 type;
    uint8 activation;
    uint8 deactivation;
    int32 size;
    uint16 interval;
    uint16 intervalOffset;
    uint16 duration;
    uint16 delay;
    int32 buttonTag;
    void *taggedButton;
    Animator animator;
} EntityFan;

// Object Struct
extern ObjectFan *Fan;

// Standard Entity Events
void Fan_StageLoad(void);

#endif //! OBJ_FAN_H
