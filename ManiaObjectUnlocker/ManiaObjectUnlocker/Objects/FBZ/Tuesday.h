#ifndef OBJ_TUESDAY_H
#define OBJ_TUESDAY_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxNode;
    Hitbox hitboxGondola;
    uint16 aniFrames;
    uint16 sfxElecCharge;
    uint16 sfxZap;
    uint16 sfxBossHit;
    uint16 sfxExplosion;
    uint16 sfxDrop;
} ObjectTuesday;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    uint8 links;
    uint8 invincibleTimer;
    uint8 health;
    Vector2 drawPos;
    void *linkNodes[8];
    void *parent;
    uint8 linkMask;
    uint8 nextShockFlags;
    uint8 shockFlags;
    uint8 shockType;
    uint16 timer;
    uint16 shockTimer;
    uint16 linkCount;
    Animator nodeAnimator;
    Animator gondolaAnimator;
} EntityTuesday;

// Object Struct
extern ObjectTuesday *Tuesday;

// Standard Entity Events
void Tuesday_StageLoad(void);

#endif //! OBJ_TUESDAY_H
