#ifndef OBJ_SP500_H
#define OBJ_SP500_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 printLayerID;
    Hitbox hitboxSideL;
    Hitbox hitboxSideR;
    Hitbox hitboxBottom;
    uint16 aniFrames;
    uint16 sfxBeep4;
    uint16 sfxFail;
    uint16 sfxButton2;
} ObjectSP500;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 len;
    int32 height;
    int32 offL;
    int32 offR;
    int32 startDir;
    int32 printDir;
    Vector2 srcC;
    Vector2 srcM;
    Vector2 srcY;
    int32 printRowID;
    int32 rowPrintPos;
    int32 timer;
    uint8 activePlayers;
    uint8 playerTimers[2];
    int32 unused;
    bool32 showGreenLight;
    bool32 showRedLight;
    int32 curPrintDir;
    int32 inkColor;
    Vector2 targetPos;
    Entity *storedEntity;
    Animator animator;
} EntitySP500;

// Object Struct
extern ObjectSP500 *SP500;

// Standard Entity Events
void SP500_StageLoad(void);

#endif //! OBJ_SP500_H
