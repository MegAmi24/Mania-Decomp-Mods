#ifndef OBJ_MISC_H
#define OBJ_MISC_H

#include "GameAPI/Game.h"

#define COMPETITION_STAGE_COUNT (12)

// created so I can easily set up times in an array
typedef struct {
    int32 minutes;
    int32 seconds;
    int32 milliseconds;
} vsTime;

// Object Class
typedef struct {
    RSDK_OBJECT
} ObjectCompetitionSession;

// Entity Class
typedef struct {
    RSDK_ENTITY
    bool32 inMatch;
    int32 playerCount;
    int32 stageIndex;
    int32 zoneID;
    int32 actID;
    int32 matchID;
    int32 matchCount;
    int32 itemMode;
#if MANIA_USE_PLUS
    int32 swapType;
#endif
    bool32 completedStages[COMPETITION_STAGE_COUNT];
    uint8 playerID[PLAYER_COUNT];
    uint8 matchWinner[COMPETITION_STAGE_COUNT];
    int32 rings[PLAYER_COUNT];
    int32 score[PLAYER_COUNT];
    int32 items[PLAYER_COUNT];
    vsTime time[PLAYER_COUNT];
    uint8 finishState[PLAYER_COUNT];
    int32 totalRings[PLAYER_COUNT];
    int32 wins[PLAYER_COUNT];
    int32 lives[PLAYER_COUNT];
#if MANIA_USE_PLUS
    int32 screenBorderType[SCREEN_COUNT];
    int32 displayMode;
    int32 inputSlots[PLAYER_COUNT];
    int32 prevMatchID;
#endif
} EntityCompetitionSession;

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 actID;
    StateMachine(stageFinishCallback);
    bool32 shouldRecoverPlayers; // a little misleading, forces the player on-screen before an act transition if enabled
    StateMachine(vsSwapCB[0x10]);
    int32 vsSwapCBCount;
#if MANIA_USE_PLUS
    int32 playerSwapEnabled[PLAYER_COUNT];
    uint8 swapPlayerID;
    uint8 swapPlayerCount;
    uint8 preSwapPlayerIDs[PLAYER_COUNT];
    uint8 swappedPlayerIDs[PLAYER_COUNT];
#else
    bool32 playerSwapEnabled;
#endif
    int32 listPos;
    int32 prevListPos;
    int32 ringFrame;
    int32 timer;
    int32 persistentTimer;
    int32 cameraBoundsL[PLAYER_COUNT];
    int32 cameraBoundsR[PLAYER_COUNT];
    int32 cameraBoundsT[PLAYER_COUNT];
    int32 cameraBoundsB[PLAYER_COUNT];
    int32 playerBoundsL[PLAYER_COUNT];
    int32 playerBoundsR[PLAYER_COUNT];
    int32 playerBoundsT[PLAYER_COUNT];
    int32 playerBoundsB[PLAYER_COUNT];
    int32 deathBoundary[PLAYER_COUNT];
    int32 playerBoundActiveL[PLAYER_COUNT];
    int32 playerBoundActiveR[PLAYER_COUNT];
    int32 playerBoundActiveT[PLAYER_COUNT];
    int32 playerBoundActiveB[PLAYER_COUNT];
    int32 autoScrollSpeed;
    bool32 setATLBounds;
    bool32 gotTimeOver;
    StateMachine(timeOverCallback);
    uint16 collisionLayers;
    uint16 fgLayer[2]; // { lowPriority, highPriority }
    uint16 moveLayer;
#if MANIA_USE_PLUS
    uint16 scratchLayer;
#endif
    uint16 fgLayerMask[2]; // { lowPriority, highPriority }
    uint16 moveLayerMask;
    uint8 fgDrawGroup[2];     // { lowPriority, highPriority }
    uint8 objectDrawGroup[2]; // { lowPriority, highPriority }
    uint8 playerDrawGroup[2]; // { lowPriority, highPriority }
    uint8 hudDrawGroup;
    uint16 sfxFail;
#if MANIA_USE_PLUS
    EntityBase entityStorage[16];
    int32 screenPosX[PLAYER_COUNT];
    int32 screenPosY[PLAYER_COUNT];
    bool32 swapGameMode;
    bool32 teleportActionActive;
    int32 randSeed;
#endif
} ObjectZone;

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxRock;
    Hitbox hitboxSpikeball;
    uint16 aniFrames;
    uint16 sfxSizzle;
} ObjectLRZConvItem;

// Object Class
typedef struct {
    RSDK_OBJECT
} ObjectDebris;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 gravityStrength;
    int32 rotSpeed;
    Vector2 scaleSpeed;
    int32 delay;
    Animator animator;
} EntityDebris;

extern Vector2 (*LRZConvItem_HandleLRZConvPhys)(void *e);

extern StateMachine(Debris_State_Fall);

#endif //! OBJ_MISC_H
