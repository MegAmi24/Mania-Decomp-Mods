#ifndef OBJ_LAVAFALL_H
#define OBJ_LAVAFALL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitbox;
    uint8 lavaSfxTimer;
    bool32 playingLavaSfx;
    uint16 sfxLava;
} ObjectLavaFall;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Animator animator;
    uint16 interval;
    uint16 intervalOffset;
    uint16 duration;
    int32 timer;
} EntityLavaFall;

// Object Struct
extern ObjectLavaFall *LavaFall;

// Standard Entity Events
void LavaFall_StageLoad(void);

#endif //! OBJ_LAVAFALL_H
