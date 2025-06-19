#ifndef OBJ_AIZTORNADO_H
#define OBJ_AIZTORNADO_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    TABLE(int32 flameOffsets[5], { -0x20000, -0x10000, 0x00000, 0x10000, 0x20000 });
    uint16 aniFrames;
} ObjectAIZTornado;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 collideTimer; // unused here (used in MSZ/Tornado)
    int32 turnAngle;
    bool32 isStood;
    bool32 showFlame;
    int32 storeY;       // unused here (used in MSZ/Tornado)
    int32 gravityForce; // unused here (used in MSZ/Tornado)
    Vector2 prevPos;
    Vector2 movePos;
    Vector2 newPos;
    Vector2 moveVelocity;
    bool32 disableInteractions;
    int32 offsetX; // unused here (used in MSZ/Tornado)
    Animator animatorTornado;
    Animator animatorPropeller;
    Animator animatorFlame;
    Animator animatorPilot;
} EntityAIZTornado;

// Object Struct
extern ObjectAIZTornado *AIZTornado;

// Standard Entity Events
void AIZTornado_StageLoad(void);

#endif //! OBJ_AIZTORNADO_H
