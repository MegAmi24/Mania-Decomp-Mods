#ifndef OBJ_BSS_MESSAGE_H
#define OBJ_BSS_MESSAGE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectBSS_Message;

typedef struct {
    uint16 redFrames;
} ModObjectBSS_Message;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 messageFinishTimer;
    bool32 fadeEnabled;
    int32 color;
    bool32 saveInProgress;
    Animator leftAnimator;
    Animator rightAnimator;
} EntityBSS_Message;

// Object Struct
extern ObjectBSS_Message *BSS_Message;
extern ModObjectBSS_Message *Mod_BSS_Message;

void BSS_Message_StageLoad(void);

#endif //! OBJ_BSS_MESSAGE_H
