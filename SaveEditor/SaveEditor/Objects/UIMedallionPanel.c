#include "GameAPI/Game.h"
#include "UIMedallionPanel.h"
#include "UISaveSlot.h"

ObjectUIMedallionPanel *UIMedallionPanel;
ModObjectUIMedallionPanel *Mod_UIMedallionPanel;

void UIMedallionPanel_Update(void)
{
    RSDK_THIS(UIMedallionPanel);

    Mod.Super(UIMedallionPanel->classID, SUPER_UPDATE, NULL);

    if (SceneInfo->inEditor || API_GetNoSave() || globals->saveLoaded != STATUS_OK || !GameProgress_GetProgressRAM() || !self->onScreen)
        return;

#if MANIA_USE_PLUS
    ObjectExtrasMenu *ExtrasMenu = Mod.FindObject("ExtrasMenu");
    EntityUIControl *control     = ExtrasMenu->extrasControl;
#else
    ObjectMenuSetup *MenuSetup = Mod.FindObject("MenuSetup");
    EntityUIControl *control   = MenuSetup->extras;
#endif

    if (Mod_UIMedallionPanel->state != StateMachine_None) {
        ObjectUIControl *UIControl = Mod.FindObject("UIControl");
        UIControl->lockInput       = true;
        UIControl->inputLocked     = true;

        UISaveSlot_HandleTouchControls();
        TouchInfo->count = 0;
        StateMachine_Run(Mod_UIMedallionPanel->state);
    }
    else if ((ControllerInfo[CONT_P1].keySelect.press || UISaveSlot_CheckTouchRect(0, ScreenInfo->size.y - 32, 32, ScreenInfo->size.y))
             && !control->selectionDisabled) {
        Mod_UIMedallionPanel->state = UIMedallionPanel_State_Edit;

        ProgressRAM *progress = GameProgress_GetProgressRAM();
        for (int32 m = 0; m < GAMEPROGRESS_MEDAL_COUNT; ++m) Mod_UIMedallionPanel->medals[m] = progress->medals[m];

        UIControl_ClearInputs(-1);

        // Yeah I'm just reusing the UISaveSlot variables, what of it?
        Mod_UISaveSlot->touchUp      = false;
        Mod_UISaveSlot->touchDown    = false;
        Mod_UISaveSlot->touchLeft    = false;
        Mod_UISaveSlot->touchRight   = false;
        Mod_UISaveSlot->touchConfirm = false;
        Mod_UISaveSlot->touchBack    = false;

        ObjectUIControl *UIControl = Mod.FindObject("UIControl");
        UIControl->hasTouchInput   = false;

        TouchInfo->count = 0;
    }
}

void UIMedallionPanel_StaticUpdate(void)
{
    RSDK_THIS(UIMedallionPanel);

    Mod.Super(UIMedallionPanel->classID, SUPER_STATICUPDATE, NULL);

    if (Mod_UIMedallionPanel->state != StateMachine_None) {
        UISaveSlot_HandleTouchControls();
        TouchInfo->count = 0;
    }
}

void UIMedallionPanel_Draw(void)
{
    if (Mod_UIMedallionPanel->state == StateMachine_None)
        Mod.Super(UIMedallionPanel->classID, SUPER_DRAW, NULL);
    else
        UIMedallionPanel_DrawEditor();
}

void UIMedallionPanel_StageLoad(void)
{
    Mod.Super(UIMedallionPanel->classID, SUPER_STAGELOAD, NULL);
    Mod_UIMedallionPanel->state     = StateMachine_None;
    Mod_UIMedallionPanel->selection = 0;
}

void UIMedallionPanel_State_Edit(void)
{
    RSDK_THIS(UIMedallionPanel);

    if (ControllerInfo[CONT_P1].keyRight.press) {
        int32 quarter                   = Mod_UIMedallionPanel->selection / 8;
        Mod_UIMedallionPanel->selection = ((Mod_UIMedallionPanel->selection + 1) % 8) + (8 * quarter);
        if (Mod_UIMedallionPanel->selection >= GAMEPROGRESS_MEDAL_COUNT)
            Mod_UIMedallionPanel->selection = 0;
    }
    else if (ControllerInfo[CONT_P1].keyLeft.press) {
        int32 quarter                   = Mod_UIMedallionPanel->selection / 8;
        Mod_UIMedallionPanel->selection = ((Mod_UIMedallionPanel->selection - 1) % 8) + (8 * quarter);
        if (Mod_UIMedallionPanel->selection < 0)
            Mod_UIMedallionPanel->selection += 8;
    }
    else if (ControllerInfo[CONT_P1].keyUp.press) {
        Mod_UIMedallionPanel->selection -= 8;
        if (Mod_UIMedallionPanel->selection < 0)
            Mod_UIMedallionPanel->selection += GAMEPROGRESS_MEDAL_COUNT;
    }
    else if (ControllerInfo[CONT_P1].keyDown.press) {
        Mod_UIMedallionPanel->selection += 8;
        if (Mod_UIMedallionPanel->selection >= GAMEPROGRESS_MEDAL_COUNT)
            Mod_UIMedallionPanel->selection -= GAMEPROGRESS_MEDAL_COUNT;
    }

    if (confirmPress)
        Mod_UIMedallionPanel->medals[Mod_UIMedallionPanel->selection] =
            (Mod_UIMedallionPanel->medals[Mod_UIMedallionPanel->selection] + 1) % GAMEPROGRESS_MEDAL_ID_COUNT;
    else if (ControllerInfo[CONT_P1].keySelect.press || backPress)
        UIMedallionPanel_CloseEditor_CB();

    // Process medallion cheat
    int32 key = 0;
    if (ControllerInfo[CONT_P1].keyLeft.press)
        key = 1;
    else if (ControllerInfo[CONT_P1].keyRight.press)
        key = 2;

    if (key) {
        for (int32 i = 0; i < 7; ++i) Mod_UIMedallionPanel->cheatCode[i] = Mod_UIMedallionPanel->cheatCode[i + 1];

        Mod_UIMedallionPanel->cheatCode[7] = key;
    }

    // left, left, right, right, left, right, left, right
    if (Mod_UIMedallionPanel->cheatCode[0] == 1 && Mod_UIMedallionPanel->cheatCode[1] == 1 && Mod_UIMedallionPanel->cheatCode[2] == 2
        && Mod_UIMedallionPanel->cheatCode[3] == 2 && Mod_UIMedallionPanel->cheatCode[4] == 1 && Mod_UIMedallionPanel->cheatCode[5] == 2
        && Mod_UIMedallionPanel->cheatCode[6] == 1 && Mod_UIMedallionPanel->cheatCode[7] == 2) {
        for (int32 m = 0; m < GAMEPROGRESS_MEDAL_COUNT; ++m) Mod_UIMedallionPanel->medals[m] = GAMEPROGRESS_MEDAL_GOLD;
        for (int32 i = 0; i < 7; ++i) Mod_UIMedallionPanel->cheatCode[i] = 0;

        ObjectUIWidgets *UIWidgets = Mod.FindObject("UIWidgets");
        RSDK.PlaySfx(UIWidgets->sfxEvent, false, 0xFF);
    }
}

void UIMedallionPanel_State_Wait(void) {}

void UIMedallionPanel_CloseEditor_CB(void)
{
    ProgressRAM *progress = GameProgress_GetProgressRAM();
    if (progress) {
        GameProgress_ClearBSSSave();
        for (int32 m = 0; m < GAMEPROGRESS_MEDAL_COUNT; ++m) GameProgress_GiveMedal(m, Mod_UIMedallionPanel->medals[m]);
    }

    UIWaitSpinner_StartWait();
    Mod_UIMedallionPanel->state = UIMedallionPanel_State_Wait;
    SaveGame_SaveFile(UIMedallionPanel_Edit_ExitCB);
}

#if MANIA_USE_PLUS
void UIMedallionPanel_Edit_ExitCB(bool32 success)
#else
void UIMedallionPanel_Edit_ExitCB(void)
#endif
{
    UIWaitSpinner_FinishWait();
    Menu_HandleUnlocks();
    Mod_UIMedallionPanel->state = StateMachine_None;
}

void UIMedallionPanel_DrawEditor(void)
{
    RSDK_THIS(UIMedallionPanel);
    Vector2 drawPos;

    for (int32 m = 0; m < GAMEPROGRESS_MEDAL_COUNT; ++m) {
        drawPos.x = (self->position.x - TO_FIXED(49)) + TO_FIXED(14) * (m % 8);
        drawPos.y = (self->position.y - TO_FIXED(21)) + TO_FIXED(14) * (m / 8);

        RSDK.SetSpriteAnimation(UIMedallionPanel->aniFrames, 0, &self->animator, true, Mod_UIMedallionPanel->medals[m]);

        if (!SceneInfo->inEditor && !self->animator.frameID)
            RSDK.DrawCircleOutline(drawPos.x, drawPos.y, 5, 6, 0x000000, 0xFF, INK_BLEND, false);

        drawPos.x += TO_FIXED(1);
        RSDK.DrawSprite(&self->animator, &drawPos, false);

        drawPos.x -= TO_FIXED(1);
        if (Mod_UIMedallionPanel->selection == m)
            RSDK.DrawCircleOutline(drawPos.x, drawPos.y, 5, 7, 0xF0F0F0, 0xFF, INK_NONE, false);
    }
}
