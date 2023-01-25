#ifndef OBJ_HANDLAUNCHER_H
#define OBJ_HANDLAUNCHER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxRange;
    Hitbox hitboxGrab;
    Hitbox hitboxUnused;
    bool32 dunkeyMode;
    uint16 sfxDunkey;
} ObjectHandLauncher;

// Object Struct
extern ObjectHandLauncher *HandLauncher;

#endif //! OBJ_HANDLAUNCHER_H
