#ifndef OBJ_WOODROW_H
#define OBJ_WOODROW_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxFullRange;
    Hitbox hitboxBombRange;
    Hitbox hitboxBomb;
    uint16 aniFrames;
    uint16 sfxExplosion;
    uint16 sfxPeck;
} ObjectWoodrow;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    int32 distUp;
    int32 distDown;
    uint8 activeBombCount;
    uint8 bombCount;
    uint8 bombFallDelay;
    uint8 moveDelay;
    int32 rangeMask;
    Vector2 startPos;
    uint8 startDir;
    void *parent;
    Animator animator;
} EntityWoodrow;

// Object Struct
extern ObjectWoodrow *Woodrow;

// Standard Entity Events
void Woodrow_StageLoad(void);

#endif //! OBJ_WOODROW_H
