#ifndef OBJ_MISC_H
#define OBJ_MISC_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxWheel;
    TABLE(int32 heightTable[33], { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 6, 6, 7, 8, 9, 10, 11, 12, 14, 15, 17, 19, 22, 26 });
    uint16 sfxBumper;
    uint16 unused;
} ObjectSDashWheel;

typedef struct {
    MANIA_BUTTON_BASE

    Animator mainAnimator;
    Animator knobAnimator;
    Animator shineAnimator;
    int32 cooldown;
    uint8 rotateOffset;
} EntitySDashWheel;

// Object Struct
extern ObjectSDashWheel *SDashWheel;

// Extra Entity Functions
void SDashWheel_Update(void);

#endif //! OBJ_MISC_H
