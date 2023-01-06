#ifndef OBJ_MISC_H
#define OBJ_MISC_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxBlueShield;
    uint16 sfxBubbleShield;
    uint16 sfxFireShield;
    uint16 sfxLightningShield;
    uint16 sfxInstaShield;
    uint16 sfxBubbleBounce;
    uint16 sfxFireDash;
    uint16 sfxLightningJump;
} ObjectShield;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectInvincibleStars;

// Entity Class
typedef struct {
    RSDK_ENTITY
    EntityPlayer *player;
    StateMachine(state);
    int32 type;
    int32 timer;
    int32 frameFlags;
    bool32 forceVisible;
    Animator shieldAnimator;
    Animator fxAnimator;
} EntityShield;

#endif