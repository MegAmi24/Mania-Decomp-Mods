#ifndef OBJ_DANGO_H
#define OBJ_DANGO_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxCurlRange;
    uint16 aniFrames;
    uint16 sfxBumper;
} ObjectDango;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 rollDelay;
    bool32 preventStateChange;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
} EntityDango;

// Object Struct
extern ObjectDango *Dango;

// Standard Entity Events
void Dango_StageLoad(void);

#endif //! OBJ_DANGO_H
