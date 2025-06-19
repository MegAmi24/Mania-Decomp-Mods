#ifndef OBJ_SCREWMOBILE_H
#define OBJ_SCREWMOBILE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxCockpit;
    Hitbox hitboxDepthCharge;
    bool32 playingFanSfx;
    uint8 fanSfxTimer;
    uint16 aniFrames;
    uint16 sfxButton;
    uint16 sfxEggMobile;
    uint16 sfxBigFan;
    uint16 sfxImpact;
} ObjectScrewMobile;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    Vector2 startPos;
    bool32 bombPress;
    uint8 timer;
    int32 whirlPoolTimer;
    int32 whirlpoolHeight;
    int32 invincibilityTimer;
    uint8 health;
    void *whirlpool;
    Animator mobileAnimator;
    Animator propellerAnimator;
    Animator rackAnimator;
    Animator whirlpoolAnimator;
    Animator whirlpoolTopAnimator;
    Animator whirlpoolBottomAnimator;
} EntityScrewMobile;

// Object Struct
extern ObjectScrewMobile *ScrewMobile;

// Standard Entity Events
void ScrewMobile_StageLoad(void);

#endif //! OBJ_SCREWMOBILE_H
