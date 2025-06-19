#ifndef OBJ_SPEEDBOOSTER_H
#define OBJ_SPEEDBOOSTER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    StateMachine(defaultState);
    Hitbox hitbox;
    uint16 aniFrames;
    uint16 sfxSpeedBooster;
} ObjectSpeedBooster;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 speed;
    int32 playerPos[PLAYER_COUNT];
    Vector2 drawPos;
    uint8 timer;
    uint8 playerTimer[PLAYER_COUNT];
    Animator animator;
} EntitySpeedBooster;

// Object Struct
extern ObjectSpeedBooster *SpeedBooster;

// Standard Entity Events
void SpeedBooster_StageLoad(void);

#endif //! OBJ_SPEEDBOOSTER_H
