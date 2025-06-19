#ifndef OBJ_PSZDOOR_H
#define OBJ_PSZDOOR_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxes[2];
    uint16 aniFrames;
    uint16 sfxOpen;
} ObjectPSZDoor;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 orientation;
    bool32 open;
    int32 speed;
    uint8 id;
    int32 automatic;
    void *trigger;
    bool32 shouldMove;
    Vector2 doorPos;
    Vector2 offset;
    Vector2 startPos; // its set once and never used
    Vector2 targetPos;
    Animator doorAnimator;
    Animator cogAnimator;
} EntityPSZDoor;

// Object Struct
extern ObjectPSZDoor *PSZDoor;

// Standard Entity Events
void PSZDoor_StageLoad(void);

#endif //! OBJ_PSZDOOR_H
