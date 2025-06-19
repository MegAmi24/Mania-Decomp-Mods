#ifndef OBJ_SPLATS_H
#define OBJ_SPLATS_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    StateMachine(initialState);
    Hitbox hitboxBadnikGHZ;
    Hitbox hitboxJar;
    Hitbox hitboxBadnikPGZ;
    uint16 aniFrames;
    uint16 sfxSplatsSpawn;
    uint16 sfxSplatsLand;
} ObjectSplats;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 bounceCount;
    uint8 activeCount;
    uint8 numActive;
    uint16 minDelay;
    int32 delay;
    bool32 isOnScreen;
    void *parent;
    Vector2 startPos;
    int32 startDir;
    Animator mainAnimator;
    Animator splashAnimator;
} EntitySplats;

// Object Struct
extern ObjectSplats *Splats;

// Standard Entity Events
void Splats_StageLoad(void);

#endif //! OBJ_SPLATS_H
