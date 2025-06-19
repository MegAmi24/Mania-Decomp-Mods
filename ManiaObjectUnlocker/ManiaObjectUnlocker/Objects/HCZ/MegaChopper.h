#ifndef OBJ_MEGACHOPPER_H
#define OBJ_MEGACHOPPER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxChop;
    uint16 aniFrames;
} ObjectMegaChopper;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    void *grabbedPlayer;
    Vector2 playerPos;
    uint8 playerDir;
    uint16 shakeTimer;
    uint16 shakeCount;
    uint16 lastShakeFlags;
    uint8 nibbleTimer;
    Animator animator;
} EntityMegaChopper;

// Object Struct
extern ObjectMegaChopper *MegaChopper;

// Standard Entity Events
void MegaChopper_StageLoad(void);

#endif //! OBJ_MEGACHOPPER_H
