#ifndef OBJ_LEDPANEL_H
#define OBJ_LEDPANEL_H

#include "GameAPI/Game.h"

#define LEDPANEL_TEXT_COUNT (8)
#define LEDPANEL_ROW_COUNT  (2)

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    String text;
    color panelColor;
} ObjectLEDPanel;

// Entity Class
typedef struct {
    RSDK_ENTITY
    String text[LEDPANEL_TEXT_COUNT];
    String seq[LEDPANEL_ROW_COUNT];
    String *seqPtrs[LEDPANEL_ROW_COUNT];
    int32 rowSeqPos[LEDPANEL_ROW_COUNT];
    StateMachine(stateRow[LEDPANEL_ROW_COUNT]);
    String *textPtrs[LEDPANEL_TEXT_COUNT];
    String activeText[LEDPANEL_ROW_COUNT];
    Vector2 textMovePos[LEDPANEL_ROW_COUNT];
    Vector2 textPos[LEDPANEL_ROW_COUNT];
    Vector2 textTargetPos[LEDPANEL_ROW_COUNT];
    Vector2 textMoveVel[LEDPANEL_ROW_COUNT];
    int32 activeTextSize[LEDPANEL_ROW_COUNT];
    int32 activeTextLen[LEDPANEL_ROW_COUNT];
    bool32 rowSignaled[LEDPANEL_ROW_COUNT];
    Vector2 size;
    int32 left;
    int32 right;
    int32 top;
    int32 bottom;
    int32 curXBoundaryL;
    int32 curYBoundaryT;
    int32 curXBoundaryR;
    int32 curYBoundaryB;
    int32 newXBoundaryL;
    int32 newYBoundaryT;
    int32 newXBoundaryR;
    int32 newYBoundaryB;
    Vector2 boundsMoveSpeed;
    int32 rowDelay[LEDPANEL_ROW_COUNT];
    uint8 row;
    Animator animatorText;
} EntityLEDPanel;

// Object Struct
extern ObjectLEDPanel *LEDPanel;

// Standard Entity Events
void LEDPanel_StageLoad(void);

#endif //! OBJ_LEDPANEL_H
