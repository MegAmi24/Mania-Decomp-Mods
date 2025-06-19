#ifndef OBJ_JAWZ_H
#define OBJ_JAWZ_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    uint16 aniFrames;
} ObjectJawz;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 triggerDir;
    StateMachine(state);
    Vector2 startPos;
    Animator animator;
} EntityJawz;

// Object Struct
extern ObjectJawz *Jawz;

// Standard Entity Events
void Jawz_StageLoad(void);

#endif //! OBJ_JAWZ_H
