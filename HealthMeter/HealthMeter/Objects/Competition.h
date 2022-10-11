#ifndef OBJ_COMPETITION_H
#define OBJ_COMPETITION_H

#include "GameAPI/Game.h"

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    bool32 playerFinished[PLAYER_COUNT];
    int32 timer;
    int32 seconds;
    int32 unused1;
    Animator animator;
} EntityCompetition;

// Object Class
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

// Object Struct
extern ObjectCompetition *Competition;

#endif //! OBJ_COMPETITION_H
