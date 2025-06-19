#ifndef OBJ_ACETONE_H
#define OBJ_ACETONE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxFrostThrower;
    uint16 sfxFreeze;
} ObjectAcetone;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint16 timer;
    Animator dispenseAnimator;
    Animator gustAnimator;
    uint16 interval;
    uint16 intervalOffset;
    uint16 duration;
    Hitbox hitbox;
    bool32 isActive;
    int32 maxGustCount[4];
    int32 gustCount[4];
    Vector2 gustPos[12];
} EntityAcetone;

// Object Entity
extern ObjectAcetone *Acetone;

// Standard Entity Events
void Acetone_StageLoad(void);

#endif //! OBJ_ACETONE_H
