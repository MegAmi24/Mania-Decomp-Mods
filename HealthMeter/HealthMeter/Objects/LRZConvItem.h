#ifndef OBJ_LRZCONVITEM_H
#define OBJ_LRZCONVITEM_H

#include "GameAPI/Game.h"

typedef enum {
    LRZCONVITEM_ROCK,
    LRZCONVITEM_SPIKEBALL,
} LRZConvItemTypes;

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxRock;
    Hitbox hitboxSpikeball;
    uint16 aniFrames;
    uint16 sfxSizzle;
} ObjectLRZConvItem;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    Vector2 startPos;
    int32 unused;
    Animator animator;
} EntityLRZConvItem;

// Object Struct
extern ObjectLRZConvItem *LRZConvItem;

Vector2 (*LRZConvItem_HandleLRZConvPhys)(void *e);

#endif //! OBJ_LRZCONVITEM_H
