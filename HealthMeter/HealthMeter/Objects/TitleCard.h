#ifndef OBJ_TITLECARD_H
#define OBJ_TITLECARD_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
#if MANIA_USE_PLUS
    StateMachine(finishedCB);
    StateMachine(suppressCB);
#endif
} ObjectTitleCard;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 actionTimer;
    int32 timer;
    Vector2 decorationPos;
    int32 stripPos[4];
    Vector2 vertMovePos[2];
    Vector2 vertTargetPos[2];
    Vector2 word1DecorVerts[4];
    Vector2 word2DecorVerts[4];
    Vector2 zoneDecorVerts[4];
    Vector2 stripVertsBlue[4];   // Using Mania Mode colour names since its better than anything else we did
    Vector2 stripVertsRed[4];    // Using Mania Mode colour names since its better than anything else we did
    Vector2 stripVertsOrange[4]; // Using Mania Mode colour names since its better than anything else we did
    Vector2 stripVertsGreen[4];  // Using Mania Mode colour names since its better than anything else we did
    Vector2 bgLCurtainVerts[4];
    Vector2 bgRCurtainVerts[4];
    String zoneName;
    int32 zoneCharPos[4];
    int32 zoneCharVel[4];
    int32 zoneXPos;
    Vector2 charPos[20];
    int32 charVel[20];
    int32 titleCardWord2;
    int32 word1Width;
    int32 word2Width;
    int32 word1XPos;
    int32 word2XPos;
    uint8 actID;
    int32 actNumScale;
    Vector2 actNumPos;
#if MANIA_USE_PLUS
    bool32 enableIntro;
#endif
    Animator decorationAnimator;
    Animator nameLetterAnimator;
    Animator zoneLetterAnimator;
    Animator actNumbersAnimator;
#if MANIA_USE_PLUS
    color colors[5];
#endif
} EntityTitleCard;

// Object Struct
extern ObjectTitleCard *TitleCard;

void (*Zone_TitleCard_SupressCB)(void);

void Zone_TitleCard_SupressCB_Hook(void);

#endif //! OBJ_TITLECARD_H
