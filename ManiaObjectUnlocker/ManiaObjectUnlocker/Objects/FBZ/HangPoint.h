#ifndef OBJ_HANGPOINT_H
#define OBJ_HANGPOINT_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Animator animator;
    uint16 aniFrames;
    Hitbox hitboxGrab;
} ObjectHangPoint;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 activePlayers;
    int32 moveDistance[PLAYER_COUNT];
    int32 playerTimer[PLAYER_COUNT];
    int32 pullPos;
    int32 maxVel;
    int32 length;
    uint8 speed;
} EntityHangPoint;

// Object Struct
extern ObjectHangPoint *HangPoint;

// Standard Entity Events
void HangPoint_StageLoad(void);

#endif //! OBJ_HANGPOINT_H
