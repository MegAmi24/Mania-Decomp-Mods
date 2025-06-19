#ifndef OBJ_ARMADILOID_H
#define OBJ_ARMADILOID_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxShot;
} ObjectArmadiloid;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 type;
    int32 timer;
    void *child;
    void *parent;
    Vector2 startPos;
    Hitbox hitbox;
    Animator bodyAnimator;
    Animator headAnimator;
    Animator boosterAnimator;
} EntityArmadiloid;

// Object Struct
extern ObjectArmadiloid *Armadiloid;

// Standard Entity Events
void Armadiloid_StageLoad(void);

#endif //! OBJ_ARMADILOID_H
