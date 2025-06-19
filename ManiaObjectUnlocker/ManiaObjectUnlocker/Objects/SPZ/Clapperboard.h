#ifndef OBJ_CLAPPERBOARD_H
#define OBJ_CLAPPERBOARD_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxWhack;
} ObjectClapperboard;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateCollide);
    uint8 takeID;
    int32 clapSpeed;
    int32 stoodPlayers;
    Hitbox hitbox;
    Vector2 amplitudeL;
    Vector2 amplitudeR;
    Animator clapperTopAnimator;
    Animator clapperBottomAnimator;
    Animator boardAnimator;
    Animator numbersAnimator;
} EntityClapperboard;

// Object Struct
extern ObjectClapperboard *Clapperboard;

// Standard Entity Events
void Clapperboard_StageLoad(void);

#endif //! OBJ_CLAPPERBOARD_H
