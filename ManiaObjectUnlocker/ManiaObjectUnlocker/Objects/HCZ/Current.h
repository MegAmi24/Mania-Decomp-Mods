#ifndef OBJ_CURRENT_H
#define OBJ_CURRENT_H

#include "GameAPI/Game.h"

typedef enum {
    CURRENT_C_LEFT,
    CURRENT_C_RIGHT,
    CURRENT_C_UP,
    CURRENT_C_DOWN,
    CURRENT_W_LEFT,
    CURRENT_W_RIGHT,
    CURRENT_W_UP,
    CURRENT_W_DOWN,
} CurrentTypes;

// Object Class
typedef struct {
    RSDK_OBJECT
    uint8 activePlayers;
    Animator animator;
    uint16 aniFrames;
    uint16 sfxRush;
} ObjectCurrent;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    CurrentTypes type;
    Vector2 size;
    uint8 strength;
    Hitbox hitbox;
    uint8 activePlayers;
    Vector2 playerPositions[PLAYER_COUNT];
    int32 buttonTag;
    void *taggedButton;
    bool32 activated;
    ManiaPlaneFilterTypes planeFilter;
    bool32 waterOnly;
    bool32 fbzAchievement;
    Animator animator;
} EntityCurrent;

// Object Struct
extern ObjectCurrent *Current;

// Standard Entity Events
void Current_StageLoad(void);

#endif //! OBJ_CURRENT_H
