#ifndef OBJ_BSS_HUD_H
#define OBJ_BSS_HUD_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectBSS_HUD;

typedef struct {
    uint16 redFrames;
} ModObjectBSS_HUD;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator sphereAnimator;
    Animator ringAnimator;
    Animator numbersAnimator;
} EntityBSS_HUD;

// Object Struct
extern ObjectBSS_HUD *BSS_HUD;
extern ModObjectBSS_HUD *Mod_BSS_HUD;

void BSS_HUD_StageLoad(void);

#endif //! OBJ_BSS_HUD_H
