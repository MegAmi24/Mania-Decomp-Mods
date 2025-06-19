#ifndef OBJ_DECORATION_H
#define OBJ_DECORATION_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectDecoration;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator animator;
    uint8 type;
    int32 rotSpeed;
    Vector2 repeatTimes;
    Vector2 repeatSpacing;
    bool32 additive;
} EntityDecoration;

// Object Struct
extern ObjectDecoration *Decoration;

// Standard Entity Events
void Decoration_StageLoad(void);

#endif //! OBJ_DECORATION_H
