#ifndef OBJ_UIUSERNAMEPOPUP_H
#define OBJ_UIUSERNAMEPOPUP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Entity *popup;
} ObjectUIUsernamePopup;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 delay;
    bool32 isVisible;
    Vector2 size;
    Vector2 drawPos;
    String username;
    Animator animator;
} EntityUIUsernamePopup;

// Object Struct
extern ObjectUIUsernamePopup *UIUsernamePopup;

// Standard Entity Events
void UIUsernamePopup_Draw(void);

#endif //! OBJ_UIUSERNAMEPOPUP_H
