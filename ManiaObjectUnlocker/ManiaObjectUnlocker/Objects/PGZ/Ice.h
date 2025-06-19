#ifndef OBJ_ICE_H
#define OBJ_ICE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxPlayerBlockInner;
    Hitbox hitboxPlayerBlockOuter;
    int32 playerTimers[PLAYER_COUNT];
    uint16 sfxFreeze;
    uint16 sfxLedgeBreak;
    uint16 sfxWindowShatter;
    uint16 sfxStruggle;
} ObjectIce;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    uint8 size;
    uint8 type;
    uint8 subType;
    uint8 subFlip;
    bool32 bottomSmash;
    bool32 knuxSmash;
    uint8 timer;
    uint8 animationID;
    Animator blockAnimator;
    Animator contentsAnimator;
    Animator altContentsAnimator;
    Animator glintAnimator;
    void *playerPtr;
    Vector2 playerMoveOffset;
    Vector2 contentsOffset;
    int32 glintTimer;
    Hitbox hitboxBlock;
    Hitbox hitboxFallCheck;
    Hitbox hitboxPlayerBlockCheck;
} EntityIce;

// Object Struct
extern ObjectIce *Ice;

// Standard Entity Events
void Ice_StageLoad(void);

#endif //! OBJ_ICE_H
