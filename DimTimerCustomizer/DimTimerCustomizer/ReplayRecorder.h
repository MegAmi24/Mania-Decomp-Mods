#include "GameAPI/Game.h"

#define REPLAY_MAX_FRAMECOUNT (37447)

typedef struct {
    uint32 signature;
    int32 version;
    bool32 isPacked;
    bool32 isNotEmpty;
    int32 frameCount;
    int32 startingFrame;
    int32 zoneID;
    int32 act;
    int32 characterID;
    bool32 isPlusLayout;
    int32 oscillation;
    int32 bufferSize;
    float averageFrameSize;
    int32 unused;
} ReplayHeader;

typedef struct {
    uint8 info;
    uint8 changedValues;
    uint8 inputs;
    uint8 direction;
    Vector2 position;
    Vector2 velocity;
    int32 rotation;
    uint8 anim;
    uint8 frame;
} ReplayFrame;

typedef struct {
    ReplayHeader header;
    ReplayFrame frames[REPLAY_MAX_FRAMECOUNT];
    // there's an extra 4 bytes here, but they're just padding to make the size correct
    int32 padding;
} Replay;

typedef struct {
    RSDK_ENTITY
} EntityPlayer;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateLate);
    StateMachine(ghostPlayerState);
    StateMachine(prevPlayerState);
    StateMachine(curPlayerState);
    uint16 animID;
    uint16 frameID;
    EntityPlayer *player;
    int32 paused;
    int32 changeFlags;
    int32 isGhostPlayback;
    int32 replayFrame;
    int32 maxFrameCount;
    int32 replayStopDelay;
    uint8 storedInputs;
    uint8 storedDirection;
    Vector2 storedPos;
    Vector2 storedVel;
    int32 storedRotation;
    int32 storedSpeed;
    uint8 storedAnim;
    uint16 storedFrame;
    int32 ghostAlpha;
} EntityReplayRecorder;

// Object Class
typedef struct {
    RSDK_OBJECT
    StateMachine(actions[64]);
    int32 frameCounter;
    Replay *recordBuffer;
    Replay *playbackBuffer;
    ReplayFrame *recordingFrames;
    ReplayFrame *playbackFrames;
    EntityReplayRecorder *recordingManager;
    EntityReplayRecorder *playbackManager;
    bool32 initialized;
    int32 startRecording;
    int32 startPlayback;
    int32 savedReplay;
    int32 startedRecording;
    int32 isReplaying;
    int32 hasSetupGhostVS;
    int32 hasSetupGhostView;
    int32 passedStartLine;
    int32 reachedGoal;
    int32 packedStartFrame;
    void *fileBuffer;
    void (*loadCallback)(bool32 success);
    char filename[0x100];
    void (*saveFinishPtr)(bool32 success);
    int32 replayID;
    int32 replayRowID;
} ObjectReplayRecorder;
