#ifndef OBJ_PLATFORM_H
#define OBJ_PLATFORM_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Vector2 stoodPos[PLAYER_COUNT];
    uint16 sfxClacker;
    uint16 sfxClang;
    uint16 sfxPush;
    uint16 sfxClack;
    bool32 playingPushSfx;
    bool32 useClack;
} ObjectPlatform;

// Entity Class
typedef struct {
    MANIA_PLATFORM_BASE
} EntityPlatform;

// Object Struct
extern ObjectPlatform *Platform;

// Standard Entity Events
void Platform_StageLoad(void);

#endif //! OBJ_PLATFORM_H
