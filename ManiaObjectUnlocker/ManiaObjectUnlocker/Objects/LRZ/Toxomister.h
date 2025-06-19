#ifndef OBJ_TOXOMISTER_H
#define OBJ_TOXOMISTER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxCloud;
    uint16 aniFrames;
} ObjectToxomister;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    void *parent;
    void *grabbedPlayer;
    int32 timer;
    uint16 shakeTimer;
    uint16 shakeCount;
    uint16 prevShakeFlags;
    Animator animator;
} EntityToxomister;

// Object Struct
extern ObjectToxomister *Toxomister;

// Standard Entity Events
void Toxomister_StageLoad(void);

#endif //! OBJ_TOXOMISTER_H
