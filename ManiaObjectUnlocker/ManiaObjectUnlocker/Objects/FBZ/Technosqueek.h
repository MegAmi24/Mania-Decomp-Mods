#ifndef OBJ_TECHNOSQUEEK_H
#define OBJ_TECHNOSQUEEK_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    uint16 aniFrames;
} ObjectTechnosqueek;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    uint8 speed;
    uint16 distance;
    uint8 distRemain;
    int32 acceleration;
    int32 targetVel;
    int32 tailOffset;
    bool32 shouldTurn;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
    Animator tailAnimator;
} EntityTechnosqueek;

// Object Struct
extern ObjectTechnosqueek *Technosqueek;

// Standard Entity Events
void Technosqueek_StageLoad(void);

#endif //! OBJ_TECHNOSQUEEK_H
