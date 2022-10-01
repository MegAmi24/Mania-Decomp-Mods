#ifndef OBJ_MISC_H
#define OBJ_MISC_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
#if MANIA_USE_PLUS
    int32 buttonColors[16];
    int32 timer;
    Animator unusedAnimator1;
    Animator unusedAnimator2;
#else
    int32 timer;
    int32 buttonColors[16];
#endif
    Animator frameAnimator;
    Animator arrowsAnimator;
    uint16 uiFrames;
#if MANIA_USE_PLUS
    uint16 saveSelFrames;
#endif
    uint16 textFrames;
    uint16 fontFrames;
    uint16 sfxBleep;
    uint16 sfxAccept;
    uint16 sfxWarp;
    uint16 sfxEvent;
    uint16 sfxWoosh;
    uint16 sfxFail;
#if MANIA_USE_PLUS
    color buttonColor;
#endif
} ObjectUIWidgets;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectUIText;

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

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxThree;
    uint16 sfxTwo;
    uint16 sfxOne;
    uint16 sfxGo;
    uint16 sfxGoal;
    uint16 sfxSonicWins;
    uint16 sfxTailsWins;
    uint16 sfxKnuxWins;
#if MANIA_USE_PLUS
    uint16 sfxMightyWins;
    uint16 sfxRayWins;
#endif
    uint16 sfxNewRecordTop;
    uint16 sfxNewRecordMid;
    uint16 sfxSonic;
    uint16 sfxTails;
    uint16 sfxKnuckles;
#if MANIA_USE_PLUS
    uint16 sfxMighty;
    uint16 sfxRay;
#endif
    uint16 sfxTheWinnerIs;
    uint16 sfxPlayer1;
    uint16 sfxPlayer2;
#if MANIA_USE_PLUS
    uint16 sfxPlayer3;
    uint16 sfxPlayer4;
#endif
    uint16 sfxDrawRound;
    uint16 sfxDrawSet;
    bool32 finishedCountdown;
} ObjectAnnouncer;

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBottom;
    Hitbox hitboxMotor;
    uint8 activePlayers;
    uint16 sfxPimPom;
    uint16 sfxFail;
    Animator shineAnimator;
    uint16 aniFrames;
} ObjectLottoMachine;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectDust;

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
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    Entity *parent;
    Animator animator;
} EntityDust;

#endif