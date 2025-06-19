#ifndef OBJ_DOORTRIGGER_H
#define OBJ_DOORTRIGGER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBulb[2];
    uint16 aniFrames;
    uint16 sfxShatter;
} ObjectDoorTrigger;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 orientation;
    uint8 id;
    Animator baseAnimator;
    Animator bulbAnimator;
} EntityDoorTrigger;

// Object Struct
extern ObjectDoorTrigger *DoorTrigger;

// Standard Entity Events
void DoorTrigger_StageLoad(void);

#endif //! OBJ_DOORTRIGGER_H
