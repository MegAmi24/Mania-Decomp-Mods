#ifndef OBJ_ROTATINGSPIKES_H
#define OBJ_ROTATINGSPIKES_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectRotatingSpikes;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator pivotAnimator;
    Animator spikeBallAnimator;
    int32 pivotRadius;
    int32 spikeRadius;
    int32 spikeCount;
    int32 rotSpeed;
    int32 angleOffset;
    int32 priority;
} EntityRotatingSpikes;

// Object Struct
extern ObjectRotatingSpikes *RotatingSpikes;

// Standard Entity Events
void RotatingSpikes_StageLoad(void);

#endif //! OBJ_ROTATINGSPIKES_H
