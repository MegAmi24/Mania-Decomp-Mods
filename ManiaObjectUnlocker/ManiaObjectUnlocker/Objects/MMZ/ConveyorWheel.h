#ifndef OBJ_CONVEYORWHEEL_H
#define OBJ_CONVEYORWHEEL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitbox;
} ObjectConveyorWheel;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator animator;
} EntityConveyorWheel;

// Object Struct
extern ObjectConveyorWheel *ConveyorWheel;

// Standard Entity Events
void ConveyorWheel_StageLoad(void);

#endif //! OBJ_CONVEYORWHEEL_H
