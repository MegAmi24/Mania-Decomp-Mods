#ifndef OBJ_ORBINAUT_H
#define OBJ_ORBINAUT_H

#include "GameAPI/Game.h"

#define ORBINAUT_ORB_COUNT (4)

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxOrb;
    uint16 aniFrames;
} ObjectOrbinaut;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 planeFilter;
    Vector2 startPos;
    uint8 startDir;
    uint8 activeOrbs;
    Vector2 orbPositions[ORBINAUT_ORB_COUNT];
    bool32 fireOrbs;
    Animator animatorFace;
    Animator animatorOrb;
} EntityOrbinaut;

// Object Entity
extern ObjectOrbinaut *Orbinaut;

// Standard Entity Events
void Orbinaut_StageLoad(void);

#endif //! OBJ_ORBINAUT_H
