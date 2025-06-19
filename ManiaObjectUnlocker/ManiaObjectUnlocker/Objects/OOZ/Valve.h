#ifndef OBJ_VALVE_H
#define OBJ_VALVE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
    uint16 sfxClick;
} ObjectValve;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator valveAnimator;
    Animator wheelAnimator;
} EntityValve;

// Object Struct
extern ObjectValve *Valve;

// Standard Entity Events
void Valve_StageLoad(void);

#endif //! OBJ_VALVE_H
