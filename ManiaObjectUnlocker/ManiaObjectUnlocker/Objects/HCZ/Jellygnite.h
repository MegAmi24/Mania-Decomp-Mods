#ifndef OBJ_JELLYGNITE_H
#define OBJ_JELLYGNITE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    Hitbox hitboxUnused;
    uint16 aniFrames;
    uint16 sfxGrab;
    uint16 sfxElectrify;
} ObjectJellygnite;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    uint8 timer;
    uint8 grabDelay;
    int32 frontTentacleAngle;
    int32 oscillateAngle;
    void *grabbedPlayer;
    uint8 shakeTimer;
    uint8 shakeCount;
    uint8 lastShakeFlags;
    uint8 prevAnimationID;
    Animator bodyAnimator;
    Animator frontTentacleAnimator;
    Animator backTentacleAnimator;
} EntityJellygnite;

// Object Struct
extern ObjectJellygnite *Jellygnite;

// Standard Entity Events
void Jellygnite_StageLoad(void);

#endif //! OBJ_JELLYGNITE_H
