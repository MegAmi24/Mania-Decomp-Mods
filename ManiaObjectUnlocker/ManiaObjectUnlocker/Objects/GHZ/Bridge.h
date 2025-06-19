#ifndef OBJ_BRIDGE_H
#define OBJ_BRIDGE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectBridge;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 length;
    bool32 burnable;
    uint8 burnOffset;
    uint8 stoodEntityCount;
    uint8 timer;
    int32 stoodPos;
    int32 bridgeDepth;
    int32 depression;
    void *stoodEntity;
    int32 startPos;
    int32 endPos;
    Animator animator;
    int32 unused1;
} EntityBridge;

// Object Struct
extern ObjectBridge *Bridge;

// Standard Entity Events
void Bridge_StageLoad(void);

#endif //! OBJ_BRIDGE_H
