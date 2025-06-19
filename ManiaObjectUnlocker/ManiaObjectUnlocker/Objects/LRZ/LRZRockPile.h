#ifndef OBJ_LRZROCKPILE_H
#define OBJ_LRZROCKPILE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxWall;
    Hitbox hitboxFloorTopSolid;
    Hitbox hitboxFloorAllSolid;
    uint16 sfxLedgeBreak;
    uint16 aniFrames;
    uint16 particleFrames;
} ObjectLRZRockPile;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    uint16 delay;
    bool32 debugParticles;
    bool32 unbreakable;
    ManiaPlaneFilterTypes planeFilter;
    bool32 onlyKnux;
#if MANIA_USE_PLUS
    bool32 onlyMighty;
#endif
    int32 rockDebrisInfo[32 * 6];
    uint8 debrisCount;
    int32 timer;
    int32 destroyTimer;
    Vector2 startPos;
    Animator animator;
    bool32 canCollapse;
    Hitbox hitbox;
} EntityLRZRockPile;

// Object Struct
extern ObjectLRZRockPile *LRZRockPile;

// Standard Entity Events
void LRZRockPile_StageLoad(void);

#endif //! OBJ_LRZROCKPILE_H
