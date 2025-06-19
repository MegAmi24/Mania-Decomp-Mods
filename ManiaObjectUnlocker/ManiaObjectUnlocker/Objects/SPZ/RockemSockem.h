#ifndef OBJ_ROCKEMSOCKEM_H
#define OBJ_ROCKEMSOCKEM_H

#include "GameAPI/Game.h"

// Extras
#define ROCKEMSOCKEM_COIL_COUNT (6)

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
    uint16 sfxRockemSockem;
} ObjectRockemSockem;

// Entity Class
typedef struct {
    RSDK_ENTITY
    int32 bounceTimer;
    int32 reboundTimer;
    Vector2 drawPos;
    Vector2 startPos;
    Vector2 jointPositions[ROCKEMSOCKEM_COIL_COUNT];
    Vector2 unused1[ROCKEMSOCKEM_COIL_COUNT];
    int32 jointRotations[ROCKEMSOCKEM_COIL_COUNT];
    int32 angleVel;
    int32 unused2;
    Animator baseAnimator;
    Animator jointAnimator;
    Animator ballAnimator;
} EntityRockemSockem;

// Object Struct
extern ObjectRockemSockem *RockemSockem;

// Standard Entity Events
void RockemSockem_StageLoad(void);

#endif //! OBJ_ROCKEMSOCKEM_H
