#ifndef OBJ_DIRECTORCHAIR_H
#define OBJ_DIRECTORCHAIR_H

#include "GameAPI/Game.h"

typedef enum {
    DIRECTORCHAIR_CLOSED,
    DIRECTORCHAIR_STRETCHED,
} DirectorChairTypes;

// Object Class
typedef struct {
    RSDK_OBJECT
    uint8 extendCount;
    uint8 retractCount;
    uint16 aniFrames;
    Hitbox hitboxChair;
    Hitbox hitboxL;
    Hitbox hitboxR;
    uint16 sfxUnravel;
    uint16 sfxExtend;
    uint16 sfxRetract;
} ObjectDirectorChair;

// Entity Class
typedef struct {
    // Platform "Inherit"
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateCollide);
    int32 type;
    Vector2 amplitude;
    int32 speed;
    bool32 hasTension;
    int8 frameID;
    uint8 collision;
    Vector2 tileOrigin;
    Vector2 centerPos;
    Vector2 drawPos;
    Vector2 collisionOffset;
    int32 stood;
    int32 timer;
    int32 size;
    uint8 stoodPlayers;
    uint8 pushPlayersL;
    uint8 pushPlayersR;
    Hitbox hitbox;
    Animator animator;
    int32 childCount;

    Animator scissorAnimator;
    int32 extendVel;
    int32 minRetract;
    int32 initExtendVel;
} EntityDirectorChair;

// Object Struct
extern ObjectDirectorChair *DirectorChair;

// Standard Entity Events
void DirectorChair_StageLoad(void);

#endif //! OBJ_DIRECTORCHAIR_H
