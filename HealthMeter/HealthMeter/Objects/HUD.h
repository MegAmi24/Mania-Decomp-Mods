#ifndef OBJ_HUD_H
#define OBJ_HUD_H

#include "GameAPI/Game.h"
#include "Player.h"
#include "Misc.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
#if GAME_VERSION != VER_100
    uint16 superButtonFrames;
#endif
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
#if GAME_VERSION != VER_100
    int32 actionPromptPos;
#endif
#if MANIA_USE_PLUS
    StateMachine(vsStates[PLAYER_COUNT]);
    Vector2 vsScorePos[PLAYER_COUNT];
    Vector2 vsTimePos[PLAYER_COUNT];
    Vector2 vsRingsPos[PLAYER_COUNT];
    Vector2 vsLifePos[PLAYER_COUNT];
    int32 vsTargetPos[PLAYER_COUNT];
    int32 screenID;
#endif
#if GAME_VERSION != VER_100
    int32 timeFlashFrame;
#endif
    int32 ringFlashFrame;
    bool32 enableTimeFlash;
    bool32 enableRingFlash;
    Animator hudElementsAnimator;
    Animator numbersAnimator;
    Animator hyperNumbersAnimator;
    Animator lifeIconAnimator;
    Animator playerIDAnimator;
#if GAME_VERSION != VER_100
    Animator superIconAnimator;
    Animator superButtonAnimator;
#endif
#if MANIA_USE_PLUS
    Animator thumbsUpIconAnimator;
    Animator thumbsUpButtonAnimator;
    Animator replayClapAnimator;
    Animator saveReplayButtonAnimator;
#endif
    Vector2 healthPos;
#if MANIA_USE_PLUS
    Vector2 vsHealthPos[PLAYER_COUNT];
#endif
    Animator healthIconAnimator;
} EntityHUD;

// Object Struct
extern ObjectHUD *HUD;

// Standard Entity Events
void HUD_Update(void);
void HUD_Draw(void);
void HUD_Create(void *data);

void (*HUD_State_MoveIn)(void);
void (*HUD_State_MoveOut)(void);

// Hook Functions
void HUD_State_MoveIn_Hook(void);
bool32 HUD_State_MoveOut_Hook(bool32 skipped);

int32 (*HUD_CharacterIndexFromID)(int32 characterID);

#endif //! OBJ_HUD_H
