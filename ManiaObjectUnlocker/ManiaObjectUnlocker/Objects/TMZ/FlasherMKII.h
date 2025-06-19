#ifndef OBJ_FLASHERMKII_H
#define OBJ_FLASHERMKII_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxFlop;
    uint16 sfxZap;
} ObjectFlasherMKII;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 orientation;
    int32 type;
    int32 timer;
    Vector2 startPos;
    Animator animator;
} EntityFlasherMKII;

// Object Struct
extern ObjectFlasherMKII *FlasherMKII;

// Standard Entity Events
void FlasherMKII_StageLoad(void);

#endif //! OBJ_FLASHERMKII_H
