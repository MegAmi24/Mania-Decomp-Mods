#ifndef OBJ_TURBOSPIKER_H
#define OBJ_TURBOSPIKER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxSpike;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxLaunch;
    uint16 sfxSplash;
} ObjectTurboSpiker;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint32 type;
    int32 timer;
    int32 unused;
    Vector2 startPos;
    uint8 startDir;
    void *spike;
    Animator shellAnimator;
    Animator animator;
    bool32 playedLaunchSfx;
} EntityTurboSpiker;

// Object Struct
extern ObjectTurboSpiker *TurboSpiker;

// Standard Entity Events
void TurboSpiker_StageLoad(void);

#endif //! OBJ_TURBOSPIKER_H
