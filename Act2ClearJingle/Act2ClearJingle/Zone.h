#ifndef OBJ_ZONE_H
#define OBJ_ZONE_H

#include "GameAPI/Game.h"

typedef enum {
    TRACK_NONE       = -1,
    TRACK_STAGE      = 0,
    TRACK_INVINCIBLE = 1,
    TRACK_SNEAKERS   = 2,
    TRACK_MINIBOSS   = 3,
    TRACK_HBHBOSS    = 4,
    TRACK_EGGMAN1    = 5,
    TRACK_EGGMAN2    = 6,
    TRACK_ACTCLEAR   = 7,
    TRACK_DROWNING   = 8,
    TRACK_GAMEOVER   = 9,
    TRACK_SUPER      = 10,
#if MANIA_USE_PLUS
    TRACK_HBHMISCHIEF = 11,
    TRACK_SOUNDTEST   = 12,
#else
    TRACK_SOUNDTEST   = 11,
    TRACK_HBHMISCHIEF = 12,
#endif
    TRACK_1UP = 13,

    // Aliases/Reused slots
    TRACK_METALSONIC   = TRACK_EGGMAN1,
    TRACK_RUBYPRESENCE = TRACK_EGGMAN1,
    TRACK_BUDDYBEAT    = TRACK_EGGMAN2,
    TRACK_ERZBOSS      = TRACK_SUPER,
} MusicTracks;

// Macro to reduce ifdefs needed when calling RandSeeded with Zone->randSeed, ensures easy pre-plus compatibility
#if MANIA_USE_PLUS
#define ZONE_RAND(min, max) RSDK.RandSeeded(min, max, &Zone->randSeed)
#else
#define ZONE_RAND(min, max) RSDK.Rand(min, max)
#endif

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
    StateMachine(stateDraw);
    int32 screenID;
    int32 timer;
    int32 fadeSpeed;
    int32 fadeColor;
} EntityZone;

// Object Struct
extern ObjectZone *Zone;

// Standard Entity Events
void Zone_StaticUpdate(void);

// Extra Entity Functions
extern void (*Music_SetMusicTrack)(const char *path, uint8 track, uint32 loopPoint);

#endif //! OBJ_ZONE_H
