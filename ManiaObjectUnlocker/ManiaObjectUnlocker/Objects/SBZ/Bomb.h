#ifndef OBJ_BOMB_H
#define OBJ_BOMB_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxHurt;
    Hitbox hitboxRange;
    Hitbox hitboxShrapnel;
    uint16 aniFrames;
    uint16 sfxExplosion;
} ObjectBomb;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 planeFilter;
    Vector2 startPos;
    uint8 startDir;
    int32 timer;
    int32 fuseOffset;
    Animator mainAnimator;
    Animator fuseAnimator;
} EntityBomb;

// Object Entity
extern ObjectBomb *Bomb;

// Standard Entity Events
void Bomb_StageLoad(void);

#endif //! OBJ_BOMB_H
