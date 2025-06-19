#ifndef OBJ_RUBYPORTAL_H
#define OBJ_RUBYPORTAL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
#if MANIA_USE_PLUS
    bool32 openPortal;
#endif
} ObjectRubyPortal;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    Animator animator;
    Hitbox hitbox;
} EntityRubyPortal;

// Object Struct
extern ObjectRubyPortal *RubyPortal;

// Standard Entity Events
void RubyPortal_StageLoad(void);

#endif //! OBJ_RUBYPORTAL_H
