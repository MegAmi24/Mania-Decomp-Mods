#ifndef OBJ_ONEWAYDOOR_H
#define OBJ_ONEWAYDOOR_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxTop;
    Hitbox hitboxBottom;
    Hitbox hitboxRange;
} ObjectOneWayDoor;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 offsetY;
    Animator animator;
} EntityOneWayDoor;

// Object Struct
extern ObjectOneWayDoor *OneWayDoor;

// Standard Entity Events
void OneWayDoor_StageLoad(void);

#endif //! OBJ_ONEWAYDOOR_H
