#ifndef OBJ_SPARKRAIL_H
#define OBJ_SPARKRAIL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxPon;
} ObjectSparkRail;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Vector2 size;
    Hitbox hitbox;
} EntitySparkRail;

// Object Struct
extern ObjectSparkRail *SparkRail;

// Standard Entity Events
void SparkRail_StageLoad(void);

#endif //! OBJ_SPARKRAIL_H
