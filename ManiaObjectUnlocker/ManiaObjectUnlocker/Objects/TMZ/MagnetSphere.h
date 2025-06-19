#ifndef OBJ_MAGNETSPHERE_H
#define OBJ_MAGNETSPHERE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint8 sphereAngle[PLAYER_COUNT];
    uint8 playerAngles[PLAYER_COUNT];
    TABLE(int32 angleTable[16], { 0x20, 0x20, 0x20, 0x30, 0x40, 0x50, 0x60, 0x60, 0x60, 0xA0, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xE0 });
    uint16 aniFrames;
    uint16 sfxBumper;
    uint16 sfxPlasmaBall;
} ObjectMagnetSphere;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 activePlayers;
    uint8 playerTimers[PLAYER_COUNT];
    Animator unusedAnimator;
    Animator glassInnerAnimator;
    Animator glassOuterAnimator;
    Animator plasma1Animator;
    Animator plasma2Animator;
    Animator centerBallAnimator;
} EntityMagnetSphere;

// Object Struct
extern ObjectMagnetSphere *MagnetSphere;

// Standard Entity Events
void MagnetSphere_StageLoad(void);

#endif //! OBJ_MAGNETSPHERE_H
