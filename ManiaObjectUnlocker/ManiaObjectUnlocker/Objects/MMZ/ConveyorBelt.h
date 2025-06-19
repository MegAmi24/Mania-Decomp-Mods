#ifndef OBJ_CONVEYORBELT_H
#define OBJ_CONVEYORBELT_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectConveyorBelt;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Vector2 size;
    int32 speed;
    Animator animator;
    Hitbox hitbox;
} EntityConveyorBelt;

// Object Struct
extern ObjectConveyorBelt *ConveyorBelt;

// Standard Entity Events
void ConveyorBelt_StageLoad(void);

// Extra Entity Functions

#endif //! OBJ_CONVEYORBELT_H
