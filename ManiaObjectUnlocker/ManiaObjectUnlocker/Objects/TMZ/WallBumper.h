#ifndef OBJ_WALLBUMPER_H
#define OBJ_WALLBUMPER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxBouncer;
} ObjectWallBumper;

// Entity Class
typedef struct {
    RSDK_ENTITY
    int32 type;
    int32 size;
    bool32 reverse;
    bool32 destructible;
    Animator animator;
    Hitbox hitbox;
} EntityWallBumper;

// Object Struct
extern ObjectWallBumper *WallBumper;

// Standard Entity Events
void WallBumper_StageLoad(void);

#endif //! OBJ_WALLBUMPER_H
