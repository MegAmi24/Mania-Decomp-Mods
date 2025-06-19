#ifndef OBJ_RTELEPORTER_H
#define OBJ_RTELEPORTER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxTeleporter;
    uint16 unused1;
    uint16 unused2;
    uint16 unused3;
    uint16 sfxExplosion;
    uint16 sfxGoodFuture;
} ObjectRTeleporter;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 originY;
    int32 timer;
    Animator mainAnimator;
    Animator electricAnimator;
} EntityRTeleporter;

// Object Struct
extern ObjectRTeleporter *RTeleporter;

// Standard Entity Events
void RTeleporter_StageLoad(void);

#endif //! OBJ_RTELEPORTER_H
