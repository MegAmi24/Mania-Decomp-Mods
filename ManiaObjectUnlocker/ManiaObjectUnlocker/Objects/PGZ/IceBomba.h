#ifndef OBJ_ICEBOMBA_H
#define OBJ_ICEBOMBA_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxBomb;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxExplosion;
    uint16 sfxFreeze;
} ObjectIceBomba;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 dir;
    uint16 dist;
    uint16 dip;
    uint8 startDir;
    Vector2 startPos;
    uint32 startDist;
    Animator bodyAnimator;
    Animator wingAnimator;
    Animator bombAnimator;
} EntityIceBomba;

// Object Struct
extern ObjectIceBomba *IceBomba;

// Standard Entity Events
void IceBomba_StageLoad(void);

#endif //! OBJ_ICEBOMBA_H
