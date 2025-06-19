#ifndef OBJ_ZIPLINE_H
#define OBJ_ZIPLINE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxHandle;
} ObjectZipLine;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 activePlayers;
    Animator animator;
    int32 length;
    Vector2 startPos;
    Vector2 endPos;
    Vector2 handlePos;
    uint8 grabDelay[PLAYER_COUNT];
    Vector2 joinPos;
    int32 unused1;
} EntityZipLine;

// Object Struct
extern ObjectZipLine *ZipLine;

// Standard Entity Events
void ZipLine_StageLoad(void);

#endif //! OBJ_ZIPLINE_H
