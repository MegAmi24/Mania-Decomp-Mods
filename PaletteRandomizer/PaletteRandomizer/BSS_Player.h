#ifndef OBJ_BSS_PLAYER_H
#define OBJ_BSS_PLAYER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 jumpPressState;
    uint16 unused1; // set to 4 when hitting a yellow sphere, never *used* though
    uint16 sonicFrames;
    uint16 tailsFrames;
    uint16 knuxFrames;
    uint16 mightyFrames;
    uint16 rayFrames;
    uint16 sfxJump;
} ObjectBSS_Player;

// Entity Class
typedef struct {
    RSDK_ENTITY
    int32 gravityStrength;
    bool32 sidekick;
    StateMachine(stateInput);
    int32 controllerID;
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    Animator animator;
    Animator tailAnimator;
    uint16 aniFrames;
} EntityBSS_Player;

// Object Struct
extern ObjectBSS_Player *BSS_Player;

// Standard Entity Events
void BSS_Player_StageLoad(void);

#endif //! OBJ_BSS_PLAYER_H
