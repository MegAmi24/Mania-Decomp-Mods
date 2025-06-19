#ifndef OBJ_SENTRYBUG_H
#define OBJ_SENTRYBUG_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    TABLE(int32 orbOffsets_Attached[84], { -0x50000, 0x30000,  -0x90000, 0xA0000,  -0x70000, 0x100000, 0x70000,  0x30000,  0x30000,  0xA0000,
                                            -0x30000, 0x100000, -0x70000, 0x30000,  -0xB0000, 0xA0000,  -0x80000, 0x100000, 0x90000,  0x30000,
                                            0x60000,  0xA0000,  0,        0x100000, -0x90000, 0x30000,  -0xB0000, 0xA0000,  -0x80000, 0x100000,
                                            0x90000,  0x30000,  0x80000,  0xA0000,  0x30000,  0x100000, -0x90000, 0x30000,  -0xB0000, 0xA0000,
                                            -0x80000, 0x100000, 0x90000,  0x30000,  0xB0000,  0xA0000,  0x80000,  0x100000, 0x90000,  0x30000,
                                            0xB0000,  0xA0000,  0x80000,  0x100000, -0x90000, 0x30000,  -0x80000, 0xA0000,  -0x30000, 0x100000,
                                            0x70000,  0x30000,  0xB0000,  0xA0000,  0x80000,  0x100000, -0x90000, 0x30000,  -0x60000, 0xA0000,
                                            0,        0x100000, 0x50000,  0x30000,  0x90000,  0xA0000,  0x70000,  0x100000, -0x70000, 0x30000,
                                            -0x30000, 0xA0000,  0x30000,  0x100000 });
    TABLE(int32 dropVelR[12], { -0x10000, -0x10000, -0x20000, -0x8000, -0x10000, 0x8000, 0x10000, -0x10000, 0x20000, -0x8000, 0x10000, 0x8000 });
    TABLE(int32 dropVelL[12], { 0x10000, -0x10000, 0x20000, -0x8000, 0x10000, 0x8000, -0x10000, -0x10000, -0x20000, -0x8000, -0x10000, 0x8000 });
    Hitbox hitbox;
    uint16 meshFrames;
    uint16 sceneIndex;
    uint16 aniFrames;
    uint16 sfxPon;
    uint16 sfxSwarm;
} ObjectSentryBug;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateOrbs);
    uint8 speed;
    Vector2 amplitude;
    bool32 orbsDetached;
    bool32 showNet;
    int32 timer;
    Vector2 originPos;
    Vector2 startPos;
    void *playerPtr;
    Vector2 netPos;
    int32 netRotation;
    int32 netScale;
    int32 netColor;
    Vector2 orbPositions[6];
    Vector2 orbVelocities[6];
    Animator unusedAnimator;
    Matrix matUnused;
    Matrix matTransform;
    Matrix matWorld;
    Animator bugAnimator;
    Animator orbAnimator;
} EntitySentryBug;

// Object Struct
extern ObjectSentryBug *SentryBug;

// Standard Entity Events
void SentryBug_StageLoad(void);

#endif //! OBJ_SENTRYBUG_H
