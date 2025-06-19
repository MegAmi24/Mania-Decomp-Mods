#ifndef OBJ_MECHABU_H
#define OBJ_MECHABU_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    TABLE(int32 sawOffsets[10], { -0x150000, -0xF0000, -0x170000, -0xE0000, -0x190000, -0xA0000, -0x1A0000, -0x50000, -0x1A0000, -0x40000 });
    Hitbox hitboxSaw;
    Hitbox hitboxUnused;
    uint16 aniFrames;
    uint16 sfxSawUp;
    uint16 sfxSawDown;
} ObjectMechaBu;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    ManiaPlaneFilterTypes planeFilter;
    uint8 timer;
    uint8 sawTimer;
    Vector2 startPos;
    uint8 startDir;
    Vector2 sawPos;
    Animator badnikAnimator;
    Animator hornAnimator;
    Animator sawAnimator;
} EntityMechaBu;

// Object Struct
extern ObjectMechaBu *MechaBu;

// Standard Entity Events
void MechaBu_StageLoad(void);

#endif //! OBJ_MECHABU_H
