#ifndef OBJ_CATERKILLERJR_H
#define OBJ_CATERKILLERJR_H

#include "GameAPI/Game.h"

#define CATERKILLERJR_SEGMENT_COUNT (7)

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
} ObjectCaterkillerJr;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    Vector2 startPos;
    Vector2 bodyPosition[8];
    Vector2 bodyVelocity[8];
    int32 bodyDirection[8];
    int32 bodyTimer[8];
    int32 boundsL;
    int32 boundsR;
    Animator bodyAnimators[CATERKILLERJR_SEGMENT_COUNT];
    Animator smokePuffAnimators[3];
} EntityCaterkillerJr;

// Object Struct
extern ObjectCaterkillerJr *CaterkillerJr;

// Standard Entity Events
void CaterkillerJr_StageLoad(void);

#endif //! OBJ_CATERKILLERJR_H
