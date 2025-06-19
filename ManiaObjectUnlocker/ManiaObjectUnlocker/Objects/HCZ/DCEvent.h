#ifndef OBJ_DCEVENT_H
#define OBJ_DCEVENT_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox unusedHitbox1;
    Hitbox hitboxBomb;
    bool32 canExplodeBombs;
    uint16 aniFrames;
    uint16 eggmanFrames;
    uint16 sfxExplosion;
    uint16 sfxRumble;
    uint16 sfxImpact6;
    uint16 sfxImpact4;
} ObjectDCEvent;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 numChildren;
    uint8 type;
    int32 remainingBombs;
    int32 startY;
    int32 timer;
    Animator animator;
} EntityDCEvent;

// Object Struct
extern ObjectDCEvent *DCEvent;

// Standard Entity Events
void DCEvent_StageLoad(void);

#endif //! OBJ_DCEVENT_H
