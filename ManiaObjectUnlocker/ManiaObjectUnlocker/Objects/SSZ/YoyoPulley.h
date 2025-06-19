#ifndef OBJ_YOYOPULLEY_H
#define OBJ_YOYOPULLEY_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxHandle;
} ObjectYoyoPulley;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 activePlayers;
    Animator mainAnimator;
    Animator knobAnimator;
    Animator shineAnimator;
    Animator handleAnimator;
    uint8 pullDir;
    int32 length;
    int32 speed;
    int32 pullVelocity;
    int32 pulleyLength;
    int32 playerTimers[PLAYER_COUNT];
    Vector2 handlePos;
} EntityYoyoPulley;

// Object Struct
extern ObjectYoyoPulley *YoyoPulley;

// Standard Entity Events
void YoyoPulley_StageLoad(void);

#endif //! OBJ_YOYOPULLEY_H
