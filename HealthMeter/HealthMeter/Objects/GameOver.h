#ifndef OBJ_GAMEOVER_H
#define OBJ_GAMEOVER_H

#include "GameAPI/Game.h"

#define GAMEOVER_LETTER_COUNT (8)

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 activeScreens;
    uint16 aniFrames;
} ObjectGameOver;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 playerID;
    Vector2 barPos;
    Vector2 verts[4];
    Vector2 letterPositions[GAMEOVER_LETTER_COUNT];
    Vector2 finalOffsets[GAMEOVER_LETTER_COUNT];
    Vector2 letterPosMove[GAMEOVER_LETTER_COUNT];
    int32 letterBounceCount[GAMEOVER_LETTER_COUNT];
    int32 letterRotations[GAMEOVER_LETTER_COUNT];
    int32 letterRotateSpeed[GAMEOVER_LETTER_COUNT];
    Animator animator;
} EntityGameOver;

// Object Struct
extern ObjectGameOver *GameOver;

#endif //! OBJ_GAMEOVER_H
