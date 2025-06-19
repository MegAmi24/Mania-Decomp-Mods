#ifndef OBJ_WATER_H
#define OBJ_WATER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 waterLevel;
    int32 newWaterLevel;
    int32 targetWaterLevel;
    int32 waterMoveSpeed;
    int32 constBubbleTimer[PLAYER_COUNT];
    int32 randBubbleTimer[PLAYER_COUNT];
    int32 unused1[PLAYER_COUNT]; // unused but set to 0 on bubble timer sets. maybe an old bubble/drowning timer?
    TABLE(int32 bubbleSizes[18], { 2, 4, 2, 2, 2, 2, 4, 2, 4, 2, 2, 4, 2, 4, 2, 2, 4, 2 });
    uint16 aniFrames;
    uint16 bigBubbleFrames;
    uint16 wakeFrames;
    Hitbox hitboxPlayerBubble;
    Hitbox hitboxPoint;
    uint16 sfxSplash;
    uint16 sfxBreathe;
    uint16 sfxWarning;
    uint16 sfxDrownAlert;
    uint16 sfxDrown;
    uint16 sfxSkim;
    uint16 sfxDNAGrab;
    uint16 sfxDNABurst;
    uint16 sfxWaterLevelL;
    uint16 sfxWaterLevelR;
    int32 waterLevelChannelL;
    int32 waterLevelChannelR;
    int32 unused2;
    bool32 playingWaterLevelSfx;
    bool32 moveWaterLevel;
    int32 waterLevelVolume;
    int32 waterPalette;
    bool32 disableWaterSplash; // this is never set except for once and it's used in if ! statements to link the player or not
    int32 wakePosX[PLAYER_COUNT];
    uint8 wakeDir[PLAYER_COUNT];
    Animator wakeAnimator;
    int32 unused3;
    bool32 playingSkimSfx;
} ObjectWater;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 type;
    void *childPtr;
    int32 bubbleX;
    int8 bubbleType1;
    uint8 dudsRemaining;
    uint8 bubbleFlags;
    int8 bubbleType2;
    int32 numDuds;
    int32 countdownID;
    bool32 playerInBubble;
    Vector2 size;
    Vector2 height;
    int32 speed;
    int32 buttonTag;
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 priority;
    bool32 destroyOnTrigger;
    Hitbox hitbox;
    bool32 isBigBubble;
    int32 bigBubbleTimer;
    int32 timer;
    uint8 activePlayers;
    uint8 releasedPlayers;
    Vector2 bubbleOffset;
    Vector2 bubbleVelocity;
    void *taggedButton;
    Animator animator;
} EntityWater;

// Object Struct
extern ObjectWater *Water;

// Standard Entity Events
void Water_StageLoad(void);

#endif //! OBJ_WATER_H
