#ifndef OBJ_JUNCTIONWHEEL_H
#define OBJ_JUNCTIONWHEEL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxWheelRange;
    Hitbox hitboxSolidL;
    Hitbox hitboxSolidR;
    Hitbox hitboxSolidB;
    Hitbox hitboxEntryR;
    Hitbox hitboxEntryL;
    uint16 aniFrames;
} ObjectJunctionWheel;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator slotAnimator;
    Animator maskAnimator;
    uint8 spinDir;
} EntityJunctionWheel;

// Object Struct
extern ObjectJunctionWheel *JunctionWheel;

// Standard Entity Events
void JunctionWheel_StageLoad(void);

#endif //! OBJ_JUNCTIONWHEEL_H
