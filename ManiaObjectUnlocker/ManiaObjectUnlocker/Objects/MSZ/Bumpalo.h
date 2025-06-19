#ifndef OBJ_BUMPALO_H
#define OBJ_BUMPALO_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxBumper;
    Hitbox hitboxRange;
    Hitbox hitboxCharge;
    Hitbox hitboxUnused;
    uint16 aniFrames;
    uint16 sfxBumper;
    uint16 sfxHuff;
    uint16 sfxClack;
    uint16 sfxImpact;
} ObjectBumpalo;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    int32 timer;
    bool32 ignoreCliffs;
    bool32 wallCollided;
    Animator badnikAnimator;
    Animator huffAnimator;
    Animator dustAnimator;
} EntityBumpalo;

// Object Struct
extern ObjectBumpalo *Bumpalo;

// Standard Entity Events
void Bumpalo_StageLoad(void);

#endif //! OBJ_BUMPALO_H
