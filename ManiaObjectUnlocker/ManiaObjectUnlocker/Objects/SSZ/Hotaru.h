#ifndef OBJ_HOTARU_H
#define OBJ_HOTARU_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxTrigger;
    int32 unused1;
    int32 unused2;
    Hitbox hitboxElectricity;
    uint16 aniFrames;
} ObjectHotaru;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 quality;
    Vector2 dist;
    int32 distX1;
    int32 distX2;
    int32 speed;
    uint8 preset;
    Vector2 offset2;
    Vector2 offset1;
    uint8 hotaruDir;
    uint8 destroyedHotarus;
    Vector2 startPos;
    uint8 startDir;
    uint8 screenID;
    int32 timer;
    void *playerPtr;
    uint8 unused1;
    uint8 unused2;
    uint8 attackState;
    Vector2 electricityOffset;
    Animator mainAnimator;
    Animator bulbAnimator;
    Animator electricityAnimator;
} EntityHotaru;

// Object Struct
extern ObjectHotaru *Hotaru;

// Standard Entity Events
void Hotaru_StageLoad(void);

#endif //! OBJ_HOTARU_H
