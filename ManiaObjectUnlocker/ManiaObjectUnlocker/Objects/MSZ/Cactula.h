#ifndef OBJ_CACTULA_H
#define OBJ_CACTULA_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    uint16 aniFrames;
    uint16 sfxCactDrop;
} ObjectCactula;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 unused;
    int32 offsetY;
    bool32 droppedBomb;
    Animator bodyTopAnimator;
    Animator bodyBottomAnimator;
    Animator propellerAnimator;
} EntityCactula;

// Object Struct
extern ObjectCactula *Cactula;

// Standard Entity Events
void Cactula_StageLoad(void);

#endif //! OBJ_CACTULA_H
