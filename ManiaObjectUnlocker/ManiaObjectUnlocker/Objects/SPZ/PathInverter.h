#ifndef OBJ_PATHINVERTER_H
#define OBJ_PATHINVERTER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectPathInverter;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    Vector2 size2x;
    Vector2 size;
    void *playerPtrs[PLAYER_COUNT];
    int32 groundVelStore[PLAYER_COUNT];
    int32 playerFlipFlags[PLAYER_COUNT];
    Animator animator;
} EntityPathInverter;

// Object Struct
extern ObjectPathInverter *PathInverter;

// Standard Entity Events
void PathInverter_StageLoad(void);

#endif //! OBJ_PATHINVERTER_H
