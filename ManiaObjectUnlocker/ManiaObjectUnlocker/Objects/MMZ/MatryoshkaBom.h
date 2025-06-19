#ifndef OBJ_MATRYOSHKABOM_H
#define OBJ_MATRYOSHKABOM_H

#include "GameAPI/Game.h"

typedef enum {
    MATRYOSHKA_SIZE_BIG,
    MATRYOSHKA_SIZE_MED,
    MATRYOSHKA_SIZE_SMALL,
    MATRYOSHKA_SIZE_SHRAPNEL,
} MatryoshkaSizes;

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxHurt;
    Hitbox hitboxExplode;
    Hitbox hitboxShrapnel;
    uint16 aniFrames;
    uint16 sfxExplosion;
    uint16 sfxButton;
    uint16 sfxPon;
} ObjectMatryoshkaBom;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    ManiaPlaneFilterTypes planeFilter;
    MatryoshkaSizes size;
    bool32 canExplode;
    bool32 destroyOffscreen;
    int32 offsetY;
    int32 offsetX;
    Vector2 startPos;
    uint8 startDir;
    int32 timer;
    int32 fusePos;
    Animator bodyAnimator;
    Animator fuseAnimator;
    Animator legsAnimator;
} EntityMatryoshkaBom;

// Object Struct
extern ObjectMatryoshkaBom *MatryoshkaBom;

// Standard Entity Events
void MatryoshkaBom_StageLoad(void);

#endif //! OBJ_MATRYOSHKABOM_H
