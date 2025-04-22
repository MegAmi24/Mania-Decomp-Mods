#ifndef OBJ_UIMEDALLIONPANEL_H
#define OBJ_UIMEDALLIONPANEL_H

#include "GameAPI/Game.h"
#include "GameProgress.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectUIMedallionPanel;

// Mod Object Class
typedef struct {
    StateMachine(state);
    int32 selection;
    uint8 medals[GAMEPROGRESS_MEDAL_COUNT];
    int32 cheatCode[8];
} ModObjectUIMedallionPanel;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator animator;
} EntityUIMedallionPanel;

// Object Struct
extern ObjectUIMedallionPanel *UIMedallionPanel;
extern ModObjectUIMedallionPanel *Mod_UIMedallionPanel;

// Standard Entity Events
void UIMedallionPanel_Update(void);
void UIMedallionPanel_StaticUpdate(void);
void UIMedallionPanel_Draw(void);
void UIMedallionPanel_StageLoad(void);

// States
void UIMedallionPanel_State_Edit(void);
void UIMedallionPanel_State_Wait(void);

void UIMedallionPanel_CloseEditor_CB(void);
#if MANIA_USE_PLUS
void UIMedallionPanel_Edit_ExitCB(bool32 success);
#else
void UIMedallionPanel_Edit_ExitCB(void);
#endif

// Extra Entity Functions
void UIMedallionPanel_DrawEditor(void);

#endif //! OBJ_UIMEDALLIONPANEL_H
