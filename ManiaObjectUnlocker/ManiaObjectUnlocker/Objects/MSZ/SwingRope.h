#ifndef OBJ_SWINGROPE_H
#define OBJ_SWINGROPE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxGrabHandle;
    Hitbox hitboxHandle;
    uint16 aniFrames;
} ObjectSwingRope;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 ropeSize;
    int32 ropeGrabDelay;
    int32 rotatedAngle;
    int32 rotatedOffset;
    int32 playerLayers[PLAYER_COUNT];
    int32 angleOffset;
    Vector2 ropePos;
    Vector2 rotatePos;
    Animator ropeAnimator;
    Animator handleAnimator;
    Animator pivotAnimator;
} EntitySwingRope;

// Object Struct
extern ObjectSwingRope *SwingRope;

// Standard Entity Events
void SwingRope_StageLoad(void);

#endif //! OBJ_SWINGROPE_H
