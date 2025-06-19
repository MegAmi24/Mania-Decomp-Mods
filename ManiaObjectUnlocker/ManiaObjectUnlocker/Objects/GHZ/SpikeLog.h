#ifndef OBJ_SPIKELOG_H
#define OBJ_SPIKELOG_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    bool32 hasAchievement;
    uint8 timer;
    uint16 aniFrames;
    Hitbox hitboxSpikeLog;
    Hitbox hitboxBurnLog;
} ObjectSpikeLog;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 frame;
    Animator animator;
} EntitySpikeLog;

// Object Struct
extern ObjectSpikeLog *SpikeLog;

// Standard Entity Events
void SpikeLog_StageLoad(void);

#endif //! OBJ_SPIKELOG_H
