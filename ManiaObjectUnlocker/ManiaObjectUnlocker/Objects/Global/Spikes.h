#ifndef OBJ_SPIKES_H
#define OBJ_SPIKES_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    StateMachine(stateDraw);
    Animator verticalAnimator;
    Animator horizontalAnimator;
    uint16 aniFrames;
    int32 unused1; // both set on StageLoad but then never used
    int32 unused2; // both set on StageLoad but then never used
    uint16 sfxMove;
    uint16 sfxSpike;
} ObjectSpikes;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 type;
    bool32 moving;
    uint8 count;
    uint8 stagger;
    int16 timer;
    int32 planeFilter;
    int32 stateMove;
    int32 moveOffset;
    Vector2 collisionOffset;
    int16 glintTimer;
    uint8 shatterTimer;
    Hitbox hitbox;
    Animator animator;
} EntitySpikes;

// Object Struct
extern ObjectSpikes *Spikes;

// Standard Entity Events
void Spikes_StageLoad(void);

#endif //! OBJ_SPIKES_H
