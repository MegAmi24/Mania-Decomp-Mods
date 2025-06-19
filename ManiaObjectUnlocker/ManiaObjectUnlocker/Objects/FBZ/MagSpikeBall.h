#ifndef OBJ_MAGSPIKEBALL_H
#define OBJ_MAGSPIKEBALL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxSpikeBall;
    uint16 aniFrames;
} ObjectMagSpikeBall;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator animator;
} EntityMagSpikeBall;

// Object Struct
extern ObjectMagSpikeBall *MagSpikeBall;

// Standard Entity Events
void MagSpikeBall_StageLoad(void);

// Extra Entity Functions

#endif //! OBJ_MAGSPIKEBALL_H
