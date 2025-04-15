#ifndef OBJ_MENUSETUP_H
#define OBJ_MENUSETUP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 unused1;
    bool32 initializedMenuReturn;
    bool32 initializedMenu;
    bool32 initializedAPI;
    bool32 initializedSaves;
    int32 unused2;
    int32 unused3;
    void *fxFade;
#if !MANIA_USE_PLUS
    void *delSavePrompt;
    void *mainMenu;
    void *timeAttack;
    void *timeAttackZones;
    void *leaderboards;
    void *leaderboardWidget;
    void *leaderboardPrompt;
    void *competition;
    void *competitionRules;
    void *competitionZones;
    void *competitionRound;
    void *roundLabel;
    void *roundScoreboard;
    void *competitionTotal;
    void *totalLabel;
    void *totalScoreboard;
    void *saveSelect;
    void *noSaveMode;
    void *secrets;
    void *extras;
    void *options;
    void *optionsPrompt;
    void *video;
    void *video_win;
    void *sound;
    void *controls_win;
    void *controls_KB;
    void *controls_PS4;
    void *controls_XB1;
    void *controls_NX;
    void *controls_NX_Grip;
    void *controls_NX_JoyCon;
    void *controls_NX_Pro;
    void *language;
    int32 unused4;
    int32 unused5;
    int32 vsTotalTimer;
    int32 unused6;
    void *connectingDlg;
#endif
} ObjectMenuSetup;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(callback);
    int32 timer;
    int32 delay;
    int32 fadeShift;
    int32 fadeTimer;
    int32 fadeColor;
} EntityMenuSetup;

// Object Struct
extern ObjectMenuSetup *MenuSetup;

// Standard Entity Events
void MenuSetup_StageLoad(void);

#endif //! OBJ_MENUSETUP_H
