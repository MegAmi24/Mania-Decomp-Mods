#ifndef OBJ_MICDROP_H
#define OBJ_MICDROP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxElectrify;
} ObjectMicDrop;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Animator bodyAnimator;
    Animator wireAnimator;
    Vector2 startPos;
    uint16 distance;
    int32 timer;
    int32 swingSpeed;
    int32 swingVel;
    int32 radius;
    int32 swingPos;
} EntityMicDrop;

// Object Struct
extern ObjectMicDrop *MicDrop;

// Standard Entity Events
void MicDrop_StageLoad(void);

#endif //! OBJ_MICDROP_H
