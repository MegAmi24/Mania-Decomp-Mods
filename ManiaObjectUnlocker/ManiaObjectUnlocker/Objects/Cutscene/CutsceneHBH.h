#ifndef OBJ_CUTSCENEHBH_H
#define OBJ_CUTSCENEHBH_H

#include "GameAPI/Game.h"

typedef enum {
    HBH_GUNNER,
    HBH_SHINOBI,
    HBH_MYSTIC,
    HBH_RIDER,
    HBH_KING,
    HBH_ROGUE_FANG,
    HBH_ROGUE_BEAN,
    HBH_ROGUE_BARK,
    HBH_KINGDAMAGED,
    HBH_PILE,
    HBH_KINGTMZ2,
} HBHTypes;

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    color paletteColors[128];
} ObjectCutsceneHBH;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 characterID;
    int32 oscillate;
    int32 hiddenAtStart;
    int32 curAngle;
    int32 unused1;
    Vector2 startPos;
    Vector2 originPos;
    int32 timer;
    int32 angleOffset;
    int32 colorSet;
    color colors[128];
    bool32 useCustomPalettes;
    bool32 noGlobalTimer;
    uint16 aniFrames;
    Animator mainAnimator;
    Animator fxAnimator;
} EntityCutsceneHBH;

// Object Struct
extern ObjectCutsceneHBH *CutsceneHBH;

// Standard Entity Events
void CutsceneHBH_Create(void *data);

#endif //! OBJ_CUTSCENEHBH_H
