#ifndef OBJ_BALLHOG_H
#define OBJ_BALLHOG_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxBomb;
    uint16 aniFrames;
    uint16 sfxExplosion;
    uint16 sfxArrowHit;
    uint16 sfxDrop;
    uint16 sfxJump;
} ObjectBallHog;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 numJumps;
    uint8 bombTime;
    uint8 timer;
    uint8 jumpCount;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
} EntityBallHog;

// Object Struct
extern ObjectBallHog *BallHog;

// Standard Entity Events
void BallHog_StageLoad(void);

#endif //! OBJ_BALLHOG_H
