#ifndef OBJ_MISC_H
#define OBJ_MISC_H

#include "GameAPI/Game.h"

#if !MANIA_USE_PLUS
#define CompSession_DeriveWinner CompetitionSession_DeriveWinner
#else
#define CompSession_DeriveWinner Competition_DeriveWinner
#endif

#define COMPETITION_STAGE_COUNT (12)

#define GAMEOVER_LETTER_COUNT (8)

typedef enum {
    FINISHTYPE_NOTFINISHED,
    FINISHTYPE_GAMEOVER,
    FINISHTYPE_PASSEDSIGNPOST,
} vsFinishFlags;

typedef struct {
    int32 minutes;
    int32 seconds;
    int32 milliseconds;
} vsTime;

// Entity Classes

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

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    bool32 playerFinished[PLAYER_COUNT];
    int32 timer;
    int32 seconds;
    int32 unused1;
    Animator animator;
} EntityCompetition;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 playerID;
    Vector2 barPos;
    Vector2 verts[4];
    Vector2 letterPositions[GAMEOVER_LETTER_COUNT];
    Vector2 finalOffsets[GAMEOVER_LETTER_COUNT];
    Vector2 letterPosMove[GAMEOVER_LETTER_COUNT];
    int32 letterBounceCount[GAMEOVER_LETTER_COUNT];
    int32 letterRotations[GAMEOVER_LETTER_COUNT];
    int32 letterRotateSpeed[GAMEOVER_LETTER_COUNT];
    Animator animator;
} EntityGameOver;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    Vector2 startPos;
    int32 unused;
    Animator animator;
} EntityLRZConvItem;

// Object Classes

typedef struct {
    RSDK_OBJECT
    Vector2 centerBounds;
} ObjectCamera;

typedef struct {
    RSDK_OBJECT
    int32 unused1;
    int32 unused2;
    int32 unused3;
    int32 unused4;
    int32 unused5;
    int32 unused6;
    int32 unused7;
    int32 unused8;
    uint16 aniFrames;
    EntityCompetition *sessionManager;
    int32 unused9;
} ObjectCompetition;

typedef struct {
    RSDK_OBJECT
} ObjectCompetitionSession;

typedef struct {
    RSDK_OBJECT
    int32 activeScreens;
    uint16 aniFrames;
} ObjectGameOver;

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxRock;
    Hitbox hitboxSpikeball;
    uint16 aniFrames;
    uint16 sfxSizzle;
} ObjectLRZConvItem;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
#if MANIA_USE_PLUS
    StateMachine(finishedCB);
    StateMachine(suppressCB);
#endif
} ObjectTitleCard;

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

extern ObjectTitleCard *TitleCard;
extern ObjectZone *Zone;

void (*CompSession_DeriveWinner)(int32 playerID, int32 finishType);

Vector2 (*LRZConvItem_HandleLRZConvPhys)(void *e);

void (*Zone_TitleCard_SupressCB)(void);
void Zone_TitleCard_SupressCB_Hook(void);

void (*Zone_State_ReloadScene)(void);
void Zone_State_ReloadScene_Hook(void);

#endif //! OBJ_MISC_H
