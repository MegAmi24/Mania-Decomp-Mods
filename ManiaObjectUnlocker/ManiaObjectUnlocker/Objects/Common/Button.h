#ifndef OBJ_BUTTON_H
#define OBJ_BUTTON_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    bool32 hasEggman;
    bool32 hasPhantomRider;
    Hitbox hitboxV;
    Hitbox hitboxH;
    int32 activatePos;
    int32 buttonOffset;
    int32 hitboxOffset;
    int32 unused1; // set in stageload, but never used. no way to tell what it is
    uint16 sfxButton;
} ObjectButton;

// Entity Class
typedef struct {
    MANIA_BUTTON_BASE

    Hitbox hitboxButton;
    Animator buttonAnimator;
    Animator baseAnimator;
} EntityButton;

// Object Struct
extern ObjectButton *Button;

// Standard Entity Events
void Button_StageLoad(void);

#endif //! OBJ_BUTTON_H
