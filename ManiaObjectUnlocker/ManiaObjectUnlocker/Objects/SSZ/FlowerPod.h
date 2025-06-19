#ifndef OBJ_FLOWERPOD_H
#define OBJ_FLOWERPOD_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxPod;
    int32 unused;
    uint16 sfxExplosion;
    uint16 sfxTwinkle;
} ObjectFlowerPod;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    Vector2 startPos;
    Animator stemAnimator;
    Animator podAnimator;
} EntityFlowerPod;

// Object Struct
extern ObjectFlowerPod *FlowerPod;

// Standard Entity Events
void FlowerPod_StageLoad(void);

#endif //! OBJ_FLOWERPOD_H
