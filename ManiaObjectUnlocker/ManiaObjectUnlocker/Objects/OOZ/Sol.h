#ifndef OBJ_SOL_H
#define OBJ_SOL_H

#include "GameAPI/Game.h"

#define SOL_FLAMEORB_COUNT (4)

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxOrb;
    uint16 aniFrames;
} ObjectSol;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    uint8 activeOrbs;
    Vector2 positions[SOL_FLAMEORB_COUNT];
    int32 oscillateAngle;
    bool32 isFlameFX;
    bool32 fireOrbs;
    Animator mainAnimator;
    Animator ballAnimator;
} EntitySol;

// Object Struct
extern ObjectSol *Sol;

// Standard Entity Events
void Sol_StageLoad(void);

#endif //! OBJ_SOL_H
