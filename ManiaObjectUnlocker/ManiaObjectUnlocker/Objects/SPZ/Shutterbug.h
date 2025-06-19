#ifndef OBJ_SHUTTERBUG_H
#define OBJ_SHUTTERBUG_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxAchievement;
    uint32 pictureCount;
    uint16 aniFrames;
    uint16 snapSfx;
} ObjectShutterbug;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 snaps;
    bool32 passThrough;
    int32 snapTimer;
    uint32 numSnaps;
    void *focusTarget;
    Vector2 startPos;
    Vector2 range;
    Vector2 targetPos;
    uint8 turnTimer;
    uint8 moveDir;
    uint8 flickerTimer;
    Hitbox hitboxRange;
    Animator animator;
    Animator overlayAnimator;
} EntityShutterbug;

// Object Struct
extern ObjectShutterbug *Shutterbug;

// Standard Entity Events
void Shutterbug_StageLoad(void);

#endif //! OBJ_SHUTTERBUG_H
