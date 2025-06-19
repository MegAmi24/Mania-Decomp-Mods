#ifndef OBJ_PULLSWITCH_H
#define OBJ_PULLSWITCH_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    int32 unused;
    uint16 aniFrames;
    uint16 sfxButton;
    uint16 sfxSmogClear;
} ObjectPullSwitch;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 pullPos;
    int32 sprY;
    int32 sprHeight;
    bool32 activated;
    uint8 playerTimers[PLAYER_COUNT];
    uint8 activePlayers;
    Vector2 handlePos;
    Animator handleAnimator;
    Animator dispenserAnimator;
    Animator chainAnimator;
} EntityPullSwitch;

// Object Struct
extern ObjectPullSwitch *PullSwitch;

// Standard Entity Events
void PullSwitch_StageLoad(void);

#endif //! OBJ_PULLSWITCH_H
