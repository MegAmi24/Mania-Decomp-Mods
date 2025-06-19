#ifndef OBJ_CRATE_H
#define OBJ_CRATE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxExplosion2;
} ObjectCrate;

// Entity Class
typedef struct {
    MANIA_PLATFORM_BASE

    bool32 ignoreItemBox;
} EntityCrate;

// Object Struct
extern ObjectCrate *Crate;

// Standard Entity Events
void Crate_StageLoad(void);

#endif //! OBJ_CRATE_H
