#ifndef OBJ_INKWIPE_H
#define OBJ_INKWIPE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectInkWipe;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator animator;
} EntityInkWipe;

// Object Struct
extern ObjectInkWipe *InkWipe;

// Standard Entity Events
void InkWipe_StageLoad(void);

// Extra Entity Functions

#endif //! OBJ_INKWIPE_H
