#ifndef OBJ_TITLESETUP_H
#define OBJ_TITLESETUP_H

#include "GameAPI/Game.h"
#include "Misc.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    StateMachine(deformCB);
    int32 timedOut;
#if MANIA_USE_PLUS
    bool32 encoreStage;
#endif
    int32 machLevel;
    int32 scoreBonus;
    int32 machPoints;
    int32 rings;
    int32 timer;
    int32 ringFrame;
    int32 ringPan;
    int32 spherePan;
    int32 specialStageID;
    int32 machQuotas[3];
    uint8 playFieldLayer;
    uint16 sfxBlueSphere;
    uint16 sfxSSExit;
    uint16 sfxEmerald;
    uint16 sfxEvent;
    bool32 resetToTitle;
} ObjectUFO_Setup;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    color fadeColor;
} EntityUFO_Setup;

// Object Struct
extern ObjectUFO_Setup *UFO_Setup;

// Extra Entity Functions
extern StateMachine(UFO_Setup_State_FinishFadeout);

bool32 UFO_Setup_State_FinishFadeout_Hook(bool32 skippedState);
void UFO_Setup_RetryDLG_CB(void);
void UFO_Setup_CancelDLG_CB(void);
void UFO_Setup_ShowClearScreen(void);

#endif //! OBJ_TITLESETUP_H
