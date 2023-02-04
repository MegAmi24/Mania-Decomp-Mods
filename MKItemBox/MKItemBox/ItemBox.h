#ifndef OBJ_ITEMBOX_H
#define OBJ_ITEMBOX_H

#include "GameAPI/Game.h"
#include "Player.h"

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

// Modded Object Class
typedef struct {
    uint16 modelIndex;
    uint16 sceneIndex;
    int32 boxColorTimer;
    int32 yOffset;
    int32 angleZ;
    int32 angleY;
} ModObjectItemBox;

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
    Matrix matTempRot;
    Matrix matTransform;
    Matrix matWorld;
    Matrix matNormal;
} EntityItemBox;

// Object Struct
extern ObjectItemBox *ItemBox;
extern ModObjectItemBox *Mod_ItemBox;

// Standard Entity Events
void ItemBox_StaticUpdate(void);
void ItemBox_Draw(void);
void ItemBox_StageLoad(void);

// Extra Entity Functions
extern StateMachine(ItemBox_DebugDraw);
extern StateMachine(ItemBox_DebugSpawn);

extern void (*ItemBox_CheckHit)(void);
extern void (*ItemBox_GivePowerup)(void);
extern void (*ItemBox_Break)(EntityItemBox *itemBox, EntityPlayer *player);
extern bool32 (*ItemBox_HandleFallingCollision)(void);
extern bool32 (*ItemBox_HandlePlatformCollision)(void *platform);
extern void (*ItemBox_HandleObjectCollisions)(void);

void ItemBox_CheckHit_New(void);
void ItemBox_Break_New(EntityItemBox *itemBox, EntityPlayer *player);
void ItemBox_HandleBox(void);

// Entity States
extern StateMachine(ItemBox_State_Broken);
extern StateMachine(ItemBox_State_Break);
extern StateMachine(ItemBox_State_IconFinish);
extern StateMachine(ItemBox_State_Idle);
extern StateMachine(ItemBox_State_Falling);
extern StateMachine(ItemBox_State_Conveyor);

bool32 ItemBox_State_IconFinish_Hook(bool32 skipped);
bool32 ItemBox_State_Idle_Hook(bool32 skipped);
bool32 ItemBox_State_Falling_Hook(bool32 skipped);
bool32 ItemBox_State_Conveyor_Hook(bool32 skipped);

extern int32 (*BadnikHelpers_Oscillate)(int32 origin, int32 speed, int32 amplitude);

#endif //! OBJ_ITEMBOX_H
