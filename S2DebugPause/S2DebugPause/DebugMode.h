#ifndef OBJ_DEBUGMODE_H
#define OBJ_DEBUGMODE_H

#include "GameAPI/Game.h"

#define DEBUGMODE_ADD_OBJ(object) (*DebugMode_AddObject)(object->classID, object##_DebugDraw, object##_DebugSpawn)
#define DEBUGMODE_OBJECT_COUNT    (0x100)

// Object Class
typedef struct {
    RSDK_OBJECT
    // Never used, only set, prolly leftover from S1/S2
    int16 classIDs[DEBUGMODE_OBJECT_COUNT];
    StateMachine(draw[DEBUGMODE_OBJECT_COUNT]);
    StateMachine(spawn[DEBUGMODE_OBJECT_COUNT]);
    Animator animator;
    int32 itemID;
    int32 itemCount;
    bool32 debugActive;
    uint8 itemType;
    uint8 itemTypeCount;
    int32 exitTimer;
} ObjectDebugMode;

// Entity Class
typedef struct {
    RSDK_ENTITY
} EntityDebugMode;

// Object Struct
extern ObjectDebugMode *DebugMode;

void DebugMode_Update(void);

extern void (*Zone_StartFadeOut_MusicFade)(int32 fadeSpeed, int32 fadeColor);

#endif //! OBJ_DEBUGMODE_H
