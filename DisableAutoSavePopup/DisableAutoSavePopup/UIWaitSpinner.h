#ifndef OBJ_UIWAITSPINNER_H
#define OBJ_UIWAITSPINNER_H

#include "GameAPI/Game.h"

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    bool32 fadedIn;
    Animator animator;
} EntityUIWaitSpinner;

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    int32 timer;
    EntityUIWaitSpinner *activeSpinner;
} ObjectUIWaitSpinner;

// Object Struct
extern ObjectUIWaitSpinner *UIWaitSpinner;

// Standard Entity Events
void UIWaitSpinner_Draw(void);

#endif //! OBJ_UIWAITSPINNER_H
