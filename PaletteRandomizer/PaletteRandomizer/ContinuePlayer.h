#ifndef OBJ_CONTINUEPLAYER_H
#define OBJ_CONTINUEPLAYER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 playerAniFrames;
    uint16 tailAniFrames;
    uint16 sfxRoll;
    uint16 sfxCharge;
    uint16 sfxRelease;
} ObjectContinuePlayer;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    bool32 isPlayer2;
    int32 timer;
    int32 unused1;
    int32 unused2;
    Animator animator;
    uint16 aniFrames;
} EntityContinuePlayer;

// Object Struct
extern ObjectContinuePlayer *ContinuePlayer;

// Standard Entity Events
void ContinuePlayer_StageLoad(void);

#endif //! OBJ_CONTINUEPLAYER_H
