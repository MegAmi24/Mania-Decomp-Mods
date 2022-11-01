#ifndef OBJ_ITEMBOX_H
#define OBJ_ITEMBOX_H

#include "GameAPI/Game.h"
#include "Player.h"
#include "Misc.h"

typedef enum {
    ITEMBOX_RING,
    ITEMBOX_BLUESHIELD,
    ITEMBOX_BUBBLESHIELD,
    ITEMBOX_FIRESHIELD,
    ITEMBOX_LIGHTNINGSHIELD,
    ITEMBOX_INVINCIBLE,
    ITEMBOX_SNEAKERS,
    ITEMBOX_1UP_SONIC,
    ITEMBOX_1UP_TAILS,
    ITEMBOX_1UP_KNUX,
    ITEMBOX_EGGMAN,
    ITEMBOX_HYPERRING,
    ITEMBOX_SWAP,
    ITEMBOX_RANDOM,
    ITEMBOX_SUPER,
#if MANIA_USE_PLUS
    ITEMBOX_1UP_MIGHTY,
    ITEMBOX_1UP_RAY,
    ITEMBOX_STOCK,
#endif
    ITEMBOX_COUNT
} ItemBoxTypes;

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxItemBox;
    Hitbox hitboxHidden;
    int32 brokenFrame;
    uint16 aniFrames;
    uint16 sfxDestroy;
    uint16 sfxTeleport;
    uint16 sfxHyperRing;
#if MANIA_USE_PLUS
    uint16 sfxPowerDown;
    uint16 sfxRecovery;
#endif
} ObjectItemBox;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    ItemBoxTypes type;
    Vector2 contentsPos;
    Vector2 moveOffset;
    int32 contentsSpeed;
    Entity *storedEntity;
    int32 timer;
    bool32 isFalling;
    bool32 isContents;
    bool32 hidden;
    ManiaPlaneFilterTypes planeFilter;
    bool32 lrzConvPhys;
    Animator boxAnimator;
    Animator contentsAnimator;
    Animator overlayAnimator;
    Animator debrisAnimator;
#if MANIA_USE_PLUS
    Entity *parent;
#endif
} EntityItemBox;

// Object Struct
extern ObjectItemBox *ItemBox;

// Entity States
void (*ItemBox_GivePowerup)(void);
bool32 (*ItemBox_HandleFallingCollision)(void);

void (*ItemBox_State_Break)(void);
void (*ItemBox_State_IconFinish)(void);

bool32 ItemBox_State_Break_Hook(bool32 skipped);

#endif //! OBJ_ITEMBOX_H
