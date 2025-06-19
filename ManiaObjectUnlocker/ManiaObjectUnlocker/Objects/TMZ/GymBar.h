#ifndef OBJ_GYMBAR_H
#define OBJ_GYMBAR_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxBumper;
} ObjectGymBar;

// Entity Class
typedef struct {
    RSDK_ENTITY
    int32 type;
    int32 size;
    bool32 noSwing;
    uint8 playerTimers[PLAYER_COUNT];
    int32 maxX;
    int32 minX;
    Animator animator;
    Hitbox hitbox;
} EntityGymBar;

// Object Struct
extern ObjectGymBar *GymBar;

// Standard Entity Events
void GymBar_StageLoad(void);

#endif //! OBJ_GYMBAR_H
