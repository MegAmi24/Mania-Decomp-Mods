#ifndef OBJ_ROLLERMKII_H
#define OBJ_ROLLERMKII_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxObject;
    Hitbox hitboxInner_Rolling;
    Hitbox hitboxOuter_Rolling;
    Hitbox hitboxInner_Idle;
    Hitbox hitboxOuter_Idle;
    uint16 aniFrames;
    uint16 sfxBumper;
    uint16 sfxJump;
    uint16 sfxDropDash;
    uint16 sfxRelease;
    uint16 sfxSkidding;
} ObjectRollerMKII;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    uint8 timer;
    bool32 touchedGround;
    void *playerPtr;
    Animator animator;
} EntityRollerMKII;

// Object Struct
extern ObjectRollerMKII *RollerMKII;

// Standard Entity Events
void RollerMKII_StageLoad(void);

#endif //! OBJ_ROLLERMKII_H
