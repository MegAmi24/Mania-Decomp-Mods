#ifndef OBJ_CATERKILLER_H
#define OBJ_CATERKILLER_H

#include "GameAPI/Game.h"

#define CATERKILLER_BODY_COUNT (3)

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
} ObjectCaterkiller;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 planeFilter;
    Vector2 bodyPosition[CATERKILLER_BODY_COUNT];
    uint8 bodyDirection[CATERKILLER_BODY_COUNT];
    uint8 bodyOffset[CATERKILLER_BODY_COUNT];
    uint8 headOffset;
    uint8 timer;
    Vector2 startPos;
    uint8 startDir;
    Animator headAnimator;
    Animator bodyAnimator;
} EntityCaterkiller;

// Object Entity
extern ObjectCaterkiller *Caterkiller;

// Standard Entity Events
void Caterkiller_StageLoad(void);

#endif //! OBJ_CATERKILLER_H
