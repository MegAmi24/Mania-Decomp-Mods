#ifndef OBJ_PRINTBLOCK_H
#define OBJ_PRINTBLOCK_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Animator animator;
    uint16 aniFrames;
    uint16 sfxLetter;
} ObjectPrintBlock;

// Entity Class
typedef struct {
    MANIA_PLATFORM_BASE
    uint16 interval;
    uint16 intervalOffset;
    uint16 duration;
    uint8 letter;
} EntityPrintBlock;

// Object Struct
extern ObjectPrintBlock *PrintBlock;

// Standard Entity Events
void PrintBlock_StageLoad(void);

#endif //! OBJ_PRINTBLOCK_H
