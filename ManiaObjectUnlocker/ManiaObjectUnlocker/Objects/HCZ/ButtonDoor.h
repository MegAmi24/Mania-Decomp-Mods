#ifndef OBJ_BUTTONDOOR_H
#define OBJ_BUTTONDOOR_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxOpen;
} ObjectButtonDoor;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    Vector2 size;
    Vector2 segmentSize;
    int32 movePos;
    int32 buttonTag;
    int32 length;
    void *taggedButton;
    int32 duration;
    uint8 orientation;
    Hitbox hitbox;
    Animator animator;
} EntityButtonDoor;

// Object Struct
extern ObjectButtonDoor *ButtonDoor;

// Standard Entity Events
void ButtonDoor_StageLoad(void);

#endif //! OBJ_BUTTONDOOR_H
