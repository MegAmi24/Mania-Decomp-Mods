#ifndef OBJ_TURBINE_H
#define OBJ_TURBINE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxTurbine;
    Hitbox hitboxHandle;
    Hitbox hitboxSpikes;
    bool32 playingTurbineSfx;
} ObjectTurbine;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    uint8 activePlayers;
    int32 playerAngles[PLAYER_COUNT];
    int32 playerTimers[PLAYER_COUNT];
    Animator animator;
} EntityTurbine;

// Object Struct
extern ObjectTurbine *Turbine;

// Standard Entity Events
void Turbine_StageLoad(void);

#endif //! OBJ_TURBINE_H
