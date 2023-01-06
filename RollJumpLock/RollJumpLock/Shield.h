#ifndef OBJ_SHIELD_H
#define OBJ_SHIELD_H

#include "GameAPI/Game.h"
#include "Player.h"

typedef enum {
    SHIELDANI_BLUE,
    SHIELDANI_FIRE,
    SHIELDANI_FIREATTACK,
    SHIELDANI_LIGHTNING,
    SHIELDANI_LIGHTINGSPARK,
    SHIELDANI_BUBBLEADD,
    SHIELDANI_BUBBLE,
    SHIELDANI_BUBBLEATTACKDADD,
    SHIELDANI_BUBBLEATTACKD,
    SHIELDANI_BUBBLEATTACKUPADD,
    SHIELDANI_INSTA,
} ShieldAniIDs;

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

#endif //! OBJ_SHIELD_H
