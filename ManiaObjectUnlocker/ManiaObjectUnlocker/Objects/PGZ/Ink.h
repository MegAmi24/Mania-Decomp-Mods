#ifndef OBJ_INK_H
#define OBJ_INK_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint8 playerColors[PLAYER_COUNT];
    uint16 aniFrames;
    Hitbox hitboxBottleL;
    Hitbox hitboxBottleR;
    Hitbox hitboxBottleBottom;
} ObjectInk;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 type;
    uint8 inkedPlayers;
    Animator bottleAnimator;
    Animator contentAnimator;
    Animator splashAnimator;
} EntityInk;

// Object Struct
extern ObjectInk *Ink;

// Standard Entity Events
void Ink_StageLoad(void);

// Extra Entity Functions

#endif //! OBJ_INK_H
