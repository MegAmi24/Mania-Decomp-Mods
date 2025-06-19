#ifndef OBJ_BUZZBOMBER_H
#define OBJ_BUZZBOMBER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
} ObjectBuzzBomber;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 shotRange;
    int32 timer;
    uint8 detectedPlayer;
    Vector2 startPos;
    uint8 startDir;
    Entity *projectile;
    Animator animator;
    Animator wingAnimator;
    Animator thrustAnimator;
    Hitbox hitboxRange;
} EntityBuzzBomber;

// Object Struct
extern ObjectBuzzBomber *BuzzBomber;

// Standard Entity Events
void BuzzBomber_StageLoad(void);

#endif //! OBJ_BUZZBOMBER_H
