#ifndef OBJ_PETALPILE_H
#define OBJ_PETALPILE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    TABLE(int32 patternSize[5], { 7, 6, 6, 10, 3 });
    TABLE(int32 pattern1[14],
          { -0x10000, 0x10000, -0x8000, -0x10000, -0x5555, 0x10000, 0, -0x10000, 0x5555, 0x10000, 0x8000, -0x10000, 0x10000, 0x10000 });
    TABLE(int32 pattern2[12], { -0x10000, 0x10000, -0x5555, -0x5555, 0x10000, -0x10000, 0, 0xAAAA, 0xAAAA, 0, 0x10000, 0x10000 });
    TABLE(int32 pattern3[12], { 0x10000, 0x10000, 0x5555, -0x5555, -0x10000, -0x10000, 0, 0xAAAA, -0xAAAA, 0, -0x10000, 0x10000 });
    TABLE(int32 pattern4[20], { -0x10000, 0x10000,  -0x8000, -0x10000, -0x5555, 0x10000, 0, -0x10000, 0x5555, 0x10000,
                                0x8000,   -0x10000, 0x10000, 0x10000,  -0xAAAA, 0,       0, 0,        0xAAAA, 0 });
    TABLE(int32 pattern5[6], { 0, -0x10000, -0x10000, 0x10000, 0x10000, 0x10000 });
    uint16 aniFrames;
    uint16 sfxPetals;
} ObjectPetalPile;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    uint16 timer;
    int8 leafPattern;
    int8 tileLayer;
    Vector2 pileSize;
    Vector2 maxSpeed;
    bool32 emitterMode;
    uint8 layerID;
    Vector2 velStore;
    Vector2 distance; // dunno if this is actually a vec2 but the .y is always set to 0 so maybe?
    int32 petalVel;
    int32 unused;
    int8 petalDir;
    int32 petalRadius;
    int32 petalOffset;
    bool32 noRemoveTiles;
    Hitbox hitbox;
    Animator animator;
} EntityPetalPile;

// Object Struct
extern ObjectPetalPile *PetalPile;

// Standard Entity Events
void PetalPile_StageLoad(void);

#endif //! OBJ_PETALPILE_H
