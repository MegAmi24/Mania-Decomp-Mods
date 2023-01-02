#ifndef OBJ_DUST_H
#define OBJ_DUST_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectDust;

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
    uint8 entityStorage[16][ENTITY_SIZE];
    int32 screenPosX[PLAYER_COUNT];
    int32 screenPosY[PLAYER_COUNT];
    bool32 swapGameMode;
    bool32 teleportActionActive;
    int32 randSeed;
#endif
} ObjectZone;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    Entity *parent;
    Animator animator;
} EntityDust;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Entity *target;
    int32 screenID;
    Vector2 center;
    Vector2 targetMoveVel;
    Vector2 lastPos;
    Vector2 shakePos;
    Vector2 lookPos;
    Vector2 offset;
    bool32 disableYOffset;
    int32 centerY;
    int32 adjustY;
    int32 lerpPercent;
    int32 lerpSpeed;
    int32 lerpType;
    Vector2 endLerpPos;
    Vector2 startLerpPos;
    Vector2 boundsOffset;
    int32 boundsL;
    int32 boundsR;
    int32 boundsT;
    int32 boundsB;
} EntityCamera;

// Extra Entity Functions
void (*Dust_State_SpinDash)(void);
void (*Camera_State_FollowY)(void);

#endif //! OBJ_DUST_H
