#ifndef OBJ_UFO_HUD_H
#define OBJ_UFO_HUD_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectUFO_HUD;

// Entity Class
typedef struct {
    RSDK_ENTITY
    bool32 showRingCount;
    int32 timer;
    uint8 machPaletteBank;
    Animator hudAnimator;
    Animator numbersAnimator;
    Animator machAnimator;
    Animator stripeAnimator;
} EntityUFO_HUD;

// Object Struct
extern ObjectUFO_HUD *UFO_HUD;

// Standard Entity Events
void UFO_HUD_Update(void);

#endif //! OBJ_UFO_HUD_H
