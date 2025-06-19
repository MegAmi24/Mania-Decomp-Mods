#ifndef OBJ_TUBESPRING_H
#define OBJ_TUBESPRING_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxExit;
    Hitbox hitbox;
} ObjectTubeSpring;

// Entity Class
typedef struct {
    // "Inherits" Spring
    RSDK_ENTITY
    StateMachine(state);
    int32 type;
    FlipFlags flipFlag;
    uint8 planeFilter;
    int32 timer;
    Animator animator;
    Hitbox hitbox;
} EntityTubeSpring;

// Object Struct
extern ObjectTubeSpring *TubeSpring;

// Standard Entity Events
void TubeSpring_StageLoad(void);

#endif //! OBJ_TUBESPRING_H
