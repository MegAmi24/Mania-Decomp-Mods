#ifndef OBJ_FLAMETHROWER_H
#define OBJ_FLAMETHROWER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxFlame;
    bool32 playingFlameSfx;
    Hitbox hitboxMouthH;
    Hitbox hitboxMouthV;
    Hitbox hitboxSmallFireball;
    Hitbox hitboxMediumFireball;
    Hitbox hitboxLargeFireball;
} ObjectFlamethrower;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 orientation;
    uint8 mode;
    int32 maxDist;
    uint16 spread;
    uint16 interval;
    uint16 intervalOffset;
    uint16 duration;
    uint16 timer;
    uint16 flameAngle;
    int32 lastYVelocity;
    int32 currentDist;
    void *parent;
    Vector2 origin;
    Vector2 lastPos;
    Animator animator;
} EntityFlamethrower;

// Object Struct
extern ObjectFlamethrower *Flamethrower;

// Standard Entity Events
void Flamethrower_StageLoad(void);

#endif //! OBJ_FLAMETHROWER_H
