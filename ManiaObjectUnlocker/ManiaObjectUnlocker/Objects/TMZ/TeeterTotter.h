#ifndef OBJ_TEETERTOTTER_H
#define OBJ_TEETERTOTTER_H

#include "GameAPI/Game.h"

#define TEETERTOTTER_SEGMENT_COUNT (32)

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectTeeterTotter;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 color;
    uint32 length;
    Vector2 origin;
    int32 unused1; // never even set
    int32 playerIDs[PLAYER_COUNT];
    int32 inactiveSegments;
    int32 fallPos;
    int32 fallVelocity;
    int32 unused2; // set, but never used
    int32 segmentPosition[TEETERTOTTER_SEGMENT_COUNT];
    int32 segmentVelocity[TEETERTOTTER_SEGMENT_COUNT];
    Hitbox hitbox;
    Animator animator;
} EntityTeeterTotter;

// Object Struct
extern ObjectTeeterTotter *TeeterTotter;

// Standard Entity Events
void TeeterTotter_StageLoad(void);

#endif //! OBJ_TEETERTOTTER_H
