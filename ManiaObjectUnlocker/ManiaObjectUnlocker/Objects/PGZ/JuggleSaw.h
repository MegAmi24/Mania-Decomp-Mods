#ifndef OBJ_JUGGLESAW_H
#define OBJ_JUGGLESAW_H

#include "GameAPI/Game.h"

#define JUGGLESAW_MAX_FRIENDS (8)

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxFriendRange;
    Hitbox hitboxSaw;
    Hitbox hitboxGrabV;
    Hitbox hitboxGrabH;
    uint16 aniFrames;
    uint16 sfxExplode;
    uint16 sfxJuggle;
    uint16 sfxThrow;
} ObjectJuggleSaw;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint16 sawDelay;
    uint32 sawSpeed;
    bool32 hasSaw;
    uint16 setID;
    void *friends[JUGGLESAW_MAX_FRIENDS];
    uint8 friendCount;
    uint8 sawTimer;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
} EntityJuggleSaw;

// Object Struct
extern ObjectJuggleSaw *JuggleSaw;

// Standard Entity Events
void JuggleSaw_StageLoad(void);

#endif //! OBJ_JUGGLESAW_H
