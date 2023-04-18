#ifndef OBJ_HUD_H
#define OBJ_HUD_H

#include "GameAPI/Game.h"

#if GAME_VERSION != VER_100
typedef struct {
    uint8 padding[0x58];
    int32 saveState;
    int32 characterID;
    int32 zoneID;
    int32 lives;
    int32 score;
    int32 score1UP;
    int32 collectedEmeralds;
    int32 continues;
    int32 storedStageID;
    int32 nextSpecialStage;
    int32 collectedSpecialRings;
    int32 medalMods;
#if MANIA_USE_PLUS
    int32 zoneTimes[32];
    int32 characterFlags;
    int32 stock;
    int32 playerID; // encore playerID
#endif
} SaveRAM;

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 superButtonFrames;
#if MANIA_USE_PLUS
    uint16 sfxClick;
    uint16 sfxStarpost;
    bool32 showTAPrompt;
    bool32 replaySaveEnabled;
    int32 screenBorderType[PLAYER_COUNT];
    int32 swapCooldown;
    int32 stockFlashTimers[PLAYER_COUNT];
#endif
} ObjectHUD;

typedef struct {
#if !MANIA_USE_PLUS
    RSDK_OBJECT
    Entity *loadEntityPtr;
    void (*loadCallback)(bool32 success);
    Entity *saveEntityPtr;
    void (*saveCallback)(void);
#else
    Entity *loadEntityPtr;
    void (*loadCallback)(bool32 success);
    Entity *saveEntityPtr;
    void (*saveCallback)(bool32 success);
#endif
    SaveRAM *saveRAM;
    int32 unused1;
} ObjectSaveGame;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 scorePos;
    Vector2 timePos;
    Vector2 ringsPos;
    Vector2 lifePos;
#if MANIA_USE_PLUS
    int32 lifeFrameIDs[PLAYER_COUNT];
    int32 lives[PLAYER_COUNT];
#endif
    int32 targetPos;
    int32 actionPromptPos;
#if MANIA_USE_PLUS
    StateMachine(vsStates[PLAYER_COUNT]);
    Vector2 vsScorePos[PLAYER_COUNT];
    Vector2 vsTimePos[PLAYER_COUNT];
    Vector2 vsRingsPos[PLAYER_COUNT];
    Vector2 vsLifePos[PLAYER_COUNT];
    int32 vsTargetPos[PLAYER_COUNT];
    int32 screenID;
#endif
    int32 timeFlashFrame;
    int32 ringFlashFrame;
    bool32 enableTimeFlash;
    bool32 enableRingFlash;
    Animator hudElementsAnimator;
    Animator numbersAnimator;
    Animator hyperNumbersAnimator;
    Animator lifeIconAnimator;
    Animator playerIDAnimator;
    Animator superIconAnimator;
    Animator superButtonAnimator;
#if MANIA_USE_PLUS
    Animator thumbsUpIconAnimator;
    Animator thumbsUpButtonAnimator;
    Animator replayClapAnimator;
    Animator saveReplayButtonAnimator;
#endif
} EntityHUD;

// Object Struct
extern ObjectHUD *HUD;

// Standard Entity Events
void HUD_LateUpdate(void);

extern SaveRAM *(*SaveGame_GetSaveRAM)(void);

#endif //  GAME_VERSION
#endif //! OBJ_HUD_H
