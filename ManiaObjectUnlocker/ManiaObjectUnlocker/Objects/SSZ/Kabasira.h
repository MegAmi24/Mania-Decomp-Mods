#ifndef OBJ_KABASIRA_H
#define OBJ_KABASIRA_H

#include "GameAPI/Game.h"

#define KABASIRA_BODY_COUNT (4)

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Vector2 onScreenRange;
    uint16 aniFrames;
    uint16 sfxPon;
    uint16 sfxExplosion2;
} ObjectKabasira;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 unused1;
    int32 unused2;
    Vector2 startPos;
    uint8 startDir;
    int32 timer;
    Animator bodyAnimator;
    Animator wingsAnimator;
    int32 unused3;
} EntityKabasira;

// Object Struct
extern ObjectKabasira *Kabasira;

// Standard Entity Events
void Kabasira_StageLoad(void);

#endif //! OBJ_KABASIRA_H
