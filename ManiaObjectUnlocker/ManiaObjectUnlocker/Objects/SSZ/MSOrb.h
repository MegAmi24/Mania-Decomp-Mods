#ifndef OBJ_MSORB_H
#define OBJ_MSORB_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxOrb;
} ObjectMSOrb;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    Animator animator;
    int32 unused1;
    int32 unused2;
} EntityMSOrb;

// Object Struct
extern ObjectMSOrb *MSOrb;

// Standard Entity Events
void MSOrb_StageLoad(void);

#endif //! OBJ_MSORB_H
