#include "GameAPI/Game.h"
#include "UISaveSlot.h"

ObjectUISaveSlot *UISaveSlot;
ModObjectUISaveSlot *Mod_UISaveSlot;

bool32 UISaveSlot_State_Hook(bool32 skipped)
{
    RSDK_THIS(UISaveSlot);

    // For some reason this hook sometimes gets called even when not in the menu scene??????
    // Just return false if that happens. todo: figure out why tf this is happening
    if (!UISaveSlot || self->classID != UISaveSlot->classID)
        return false;

    if (Mod_UISaveSlot->state == StateMachine_None) {
        if (self->type != UISAVESLOT_REGULAR)
            return false;

        EntityUIControl *control = (EntityUIControl *)self->parent;
        if (!control || control->targetPos.x != self->position.x || control->position.x != control->targetPos.x)
            return false;

        if (ControllerInfo[CONT_P1].keySelect.press || UISaveSlot_CheckTouchRect(0, ScreenInfo->size.y - 32, 32, ScreenInfo->size.y)) {
            if (!self->isNewSave)
                UISaveSlot_SetupEditor();
            else {
                String msg;
                INIT_STRING(msg);

                // UIDialog_CreateDialogYesNo wasn't a public function until late June 2024, so we have to check if it's found
                if (UIDialog_CreateDialogYesNo) {
                    // Ask before initializing
                    RSDK.InitString(&msg, "THIS SAVE SLOT IS EMPTY.\nYOU WILL NEED TO INITIALIZE IT BEFORE EDITING.\nPROCEED?", 0);
                    EntityUIDialog *dialog = UIDialog_CreateDialogYesNo(&msg, UISaveSlot_InitDLG_CB, NULL, false, true);
                    if (dialog)
                        dialog->entityPtr = (Entity *)self;
                }
                else {
                    // Can't ask first, just do it
                    RSDK.InitString(&msg, "THIS SAVE SLOT IS EMPTY.\nIT WILL BE INITIALIZED BEFORE EDITING.", 0);
                    EntityUIDialog *dialog = UIDialog_CreateDialogOk(&msg, UISaveSlot_InitDLG_CB, false);
                    if (dialog)
                        dialog->entityPtr = (Entity *)self;
                }
            }
            return true;
        }
    }
    else {
        UISaveSlot_HandleTouchControls();
        TouchInfo->count = 0;
        StateMachine_Run(Mod_UISaveSlot->state);
        return true;
    }

    return false;
}

void UISaveSlot_SetupEditor(void)
{
    RSDK_THIS(UISaveSlot);

    EntityUIControl *control = (EntityUIControl *)self->parent;
    GetSaveRAMPointer();

    Mod_UISaveSlot->menuCount = -1;

    ObjectUIWidgets *UIWidgets = Mod.FindObject("UIWidgets");
    RSDK.SetSpriteAnimation(UIWidgets->fontFrames, 0, &Mod_UISaveSlot->animator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 4, &Mod_UISaveSlot->emeraldsAnimator, true, 0);

    // Initialize Options
#if MANIA_USE_PLUS
    if (!self->encoreMode) {
        AddMenuOption(SAVEEDITOR_CHAR, "CHARACTER");
    }
    else {
        AddMenuOption(SAVEEDITOR_LEADER, "LEADER");
        AddMenuOption(SAVEEDITOR_SIDEKICK, "SIDEKICK");
        AddMenuOption(SAVEEDITOR_STOCK1, "STOCK 1");
        AddMenuOption(SAVEEDITOR_STOCK2, "STOCK 2");
        AddMenuOption(SAVEEDITOR_STOCK3, "STOCK 3");
    }
    AddMenuOption(SAVEEDITOR_ZONE, "ZONE");
    if (!self->encoreMode) {
        AddMenuOption(SAVEEDITOR_LIVES, "LIVES");
    }
    AddMenuOption(SAVEEDITOR_CONTINUES, "CONTINUES");
#else
    AddMenuOption(SAVEEDITOR_CHAR, "CHARACTER");
    AddMenuOption(SAVEEDITOR_ZONE, "ZONE");
    AddMenuOption(SAVEEDITOR_LIVES, "LIVES");
#endif
    AddMenuOption(SAVEEDITOR_SCORE, "SCORE");
    AddMenuOption(SAVEEDITOR_EMERALDS, "EMERALDS");
    AddMenuOption(SAVEEDITOR_EXIT, "EXIT");

    // Initialize Strings
    RSDK.InitString(&Mod_UISaveSlot->charStrings[CHARACTER_SONIC_TAILS], "SONIC & TAILS", false);
    RSDK.InitString(&Mod_UISaveSlot->charStrings[CHARACTER_SONIC], "SONIC", false);
    RSDK.InitString(&Mod_UISaveSlot->charStrings[CHARACTER_TAILS], "TAILS", false);
    RSDK.InitString(&Mod_UISaveSlot->charStrings[CHARACTER_KNUCKLES], "KNUCKLES", false);
#if MANIA_USE_PLUS
    RSDK.InitString(&Mod_UISaveSlot->charStrings[CHARACTER_MIGHTY], "MIGHTY", false);
    RSDK.InitString(&Mod_UISaveSlot->charStrings[CHARACTER_RAY], "RAY", false);
    RSDK.InitString(&Mod_UISaveSlot->charStrings[CHARACTER_NONE], "NONE", false);
#endif

    for (uint8 m = 0; m <= Mod_UISaveSlot->menuCount; m++) RSDK.SetSpriteString(UIWidgets->fontFrames, 0, &Mod_UISaveSlot->menuStrings[m]);
    for (uint8 c = 0; c < CHARACTER_COUNT; c++) RSDK.SetSpriteString(UIWidgets->fontFrames, 0, &Mod_UISaveSlot->charStrings[c]);

    for (uint8 z = 0; z < ZONE_COUNT_SAVEFILE; z++) {
        if (z == ZONE_COUNT_SAVEFILE - 1)
            RSDK.InitString(&Mod_UISaveSlot->zoneStrings[z], "CLEAR", false);
        else
            Localization_GetZoneName(&Mod_UISaveSlot->zoneStrings[z], z);
        RSDK.SetSpriteString(UIWidgets->fontFrames, 0, &Mod_UISaveSlot->zoneStrings[z]);
    }

    Mod_UISaveSlot->state     = UISaveSlot_EditState_Main;
    Mod_UISaveSlot->stateDraw = StateMachine_None;

    Mod_UISaveSlot->mainSelection = 0;
    Mod_UISaveSlot->subSelection  = 0;
    Mod_UISaveSlot->customValue   = 0;
    Mod_UISaveSlot->valueDigits   = 0;

    Mod_UISaveSlot->processButtonCBStore = self->processButtonCB;
    self->processButtonCB                = StateMachine_None;
    Mod_UISaveSlot->backPressCBStore     = control->backPressCB;
    control->backPressCB                 = UISaveSlot_Edit_BackCB;
    Mod_UISaveSlot->yPressCBStore        = control->yPressCB;
    control->yPressCB                    = StateMachine_None;
#if MANIA_USE_PLUS
    Mod_UISaveSlot->stateInputStore = self->stateInput;
    self->stateInput                = StateMachine_None;
#endif

    Mod_UISaveSlot->touchUp      = false;
    Mod_UISaveSlot->touchDown    = false;
    Mod_UISaveSlot->touchLeft    = false;
    Mod_UISaveSlot->touchRight   = false;
    Mod_UISaveSlot->touchConfirm = false;
    Mod_UISaveSlot->touchBack    = false;

    TouchInfo->count = 0;
}

void UISaveSlot_ModCB_OnDraw(void *data)
{
    int32 group = VOID_TO_INT(data);

    if (Mod_UISaveSlot && Mod_UISaveSlot->state != StateMachine_None && group == DRAWGROUP_COUNT - 1)
        StateMachine_Run(UISaveSlot_DrawMenu);
}

void UISaveSlot_DrawMenu(void)
{
    ObjectUIBackground *UIBackground = Mod.FindObject("UIBackground");
    RSDK.DrawRect(MAINBOX_XPOS, BOX_YPOS, MAINBOX_WIDTH, BOX_HEIGHT(Mod_UISaveSlot->menuCount + 1), UIBackground->activeColors[1], 0xFF, INK_NONE,
                  true);

    Vector2 drawPos;

    // Draw Selection Arrow
    drawPos.x = TO_FIXED(MAINBOX_XPOS + 8);
    drawPos.y = TO_FIXED(BOX_YPOS + 9 + (Mod_UISaveSlot->mainSelection * OPTION_SPACING));

    Mod_UISaveSlot->animator.frameID = 30; // >
    RSDK.DrawSprite(&Mod_UISaveSlot->animator, &drawPos, true);

    // Initialize Option Text Position
    drawPos.x = TO_FIXED(MAINBOX_XPOS + 16);
    drawPos.y = TO_FIXED(BOX_YPOS + 9);

    // Draw Option Text
    for (uint8 s = 0; s <= Mod_UISaveSlot->menuCount; s++) {
        DrawOptionText(&Mod_UISaveSlot->menuStrings[s]);
    }

    if (Mod_UISaveSlot->stateDraw) {
        RSDK.DrawRect(MAINBOX_XPOS, BOX_YPOS, MAINBOX_WIDTH, BOX_HEIGHT(Mod_UISaveSlot->menuCount + 1), 0x000000, 0x80, INK_ALPHA, true);
        StateMachine_Run(Mod_UISaveSlot->stateDraw);
    }
}

void UISaveSlot_EditState_Main(void)
{
    RSDK_THIS(UISaveSlot);

    UISaveSlot_HandleUpDown(Mod_UISaveSlot->menuCount);

    if (confirmPress) {
        GetSaveRAMPointer();
        switch (Mod_UISaveSlot->menuOptions[Mod_UISaveSlot->mainSelection]) {
            default: break;
            case SAVEEDITOR_CHAR:
                Mod_UISaveSlot->state        = UISaveSlot_EditState_ManiaChar;
                Mod_UISaveSlot->stateDraw    = UISaveSlot_EditState_DrawChar;
                Mod_UISaveSlot->subSelection = saveRAM->characterID;
                break;
#if MANIA_USE_PLUS
            case SAVEEDITOR_LEADER:
                Mod_UISaveSlot->state        = UISaveSlot_EditState_EncoreLeader;
                Mod_UISaveSlot->stateDraw    = UISaveSlot_EditState_DrawChar;
                Mod_UISaveSlot->subSelection = HUD_CharacterIndexFromID(saveRAM->playerID & 0xFF);
                break;
            case SAVEEDITOR_SIDEKICK:
                Mod_UISaveSlot->state        = UISaveSlot_EditState_EncoreSidekick;
                Mod_UISaveSlot->stateDraw    = UISaveSlot_EditState_DrawChar;
                Mod_UISaveSlot->subSelection = 0;

                int32 sidekickID = (saveRAM->playerID >> 8) & 0xFF;
                if (sidekickID)
                    Mod_UISaveSlot->subSelection = HUD_CharacterIndexFromID(sidekickID) + 1;
                break;
            case SAVEEDITOR_STOCK1:
            case SAVEEDITOR_STOCK2:
            case SAVEEDITOR_STOCK3:
                Mod_UISaveSlot->state        = UISaveSlot_EditState_EncoreStock;
                Mod_UISaveSlot->stateDraw    = UISaveSlot_EditState_DrawChar;
                Mod_UISaveSlot->subSelection = 0;

                int32 stockID = (saveRAM->stock >> (8 * (Mod_UISaveSlot->menuOptions[Mod_UISaveSlot->mainSelection] - SAVEEDITOR_STOCK1))) & 0xFF;
                if (stockID)
                    Mod_UISaveSlot->subSelection = HUD_CharacterIndexFromID(stockID) + 1;
                break;
#endif
            case SAVEEDITOR_ZONE:
                Mod_UISaveSlot->state        = UISaveSlot_EditState_Zone;
                Mod_UISaveSlot->stateDraw    = UISaveSlot_EditState_DrawZone;
                Mod_UISaveSlot->subSelection = saveRAM->zoneID;
                break;
            case SAVEEDITOR_LIVES:
                Mod_UISaveSlot->state        = UISaveSlot_EditState_SetLives;
                Mod_UISaveSlot->stateDraw    = UISaveSlot_EditState_DrawSetValue;
                Mod_UISaveSlot->subSelection = 0;
                Mod_UISaveSlot->customValue  = saveRAM->lives;
                Mod_UISaveSlot->valueDigits  = 2;
                break;
#if MANIA_USE_PLUS
            case SAVEEDITOR_CONTINUES:
                Mod_UISaveSlot->state        = UISaveSlot_EditState_SetContinues;
                Mod_UISaveSlot->stateDraw    = UISaveSlot_EditState_DrawSetValue;
                Mod_UISaveSlot->subSelection = 0;
                Mod_UISaveSlot->customValue  = saveRAM->continues;
                Mod_UISaveSlot->valueDigits  = 2;
                break;
#endif
            case SAVEEDITOR_SCORE:
                if (saveRAM->saveState != SAVEGAME_COMPLETE) {
                    Mod_UISaveSlot->state        = UISaveSlot_EditState_SetScore;
                    Mod_UISaveSlot->stateDraw    = UISaveSlot_EditState_DrawSetValue;
                    Mod_UISaveSlot->subSelection = 0;
                    Mod_UISaveSlot->customValue  = saveRAM->score;
                    Mod_UISaveSlot->valueDigits  = 7;
                }
                else {
                    ObjectUIWidgets *UIWidgets = Mod.FindObject("UIWidgets");
                    RSDK.PlaySfx(UIWidgets->sfxFail, false, 255);
                }
                break;
            case SAVEEDITOR_EMERALDS:
                Mod_UISaveSlot->state        = UISaveSlot_EditState_Emeralds;
                Mod_UISaveSlot->stateDraw    = UISaveSlot_EditState_DrawEmeralds;
                Mod_UISaveSlot->subSelection = 0;
                Mod_UISaveSlot->customValue  = saveRAM->collectedEmeralds;
                Mod_UISaveSlot->valueDigits  = 7;
                break;
            case SAVEEDITOR_EXIT: UISaveSlot_CloseEditor_CB(); break;
        }
    }
    else if (backPress)
        UISaveSlot_CloseEditor_CB();
}

void UISaveSlot_EditState_ManiaChar(void)
{
    RSDK_THIS(UISaveSlot);

    int8 optionCount = 3;
#if MANIA_USE_PLUS
    if (API.CheckDLC(DLC_PLUS))
        optionCount += 2;
#endif

    UISaveSlot_HandleUpDown(optionCount);

    if (confirmPress) {
        GetSaveRAMPointer();
        saveRAM->characterID = Mod_UISaveSlot->subSelection;
        ExitSubMenu();
    }
    else if (backPress) {
        ExitSubMenu();
    }
}

#if MANIA_USE_PLUS
void UISaveSlot_EditState_EncoreLeader(void)
{
    RSDK_THIS(UISaveSlot);

    int8 optionCount = 2;
    if (API.CheckDLC(DLC_PLUS))
        optionCount += 2;

    UISaveSlot_HandleUpDown(optionCount);

    if (confirmPress) {
        GetSaveRAMPointer();
        saveRAM->playerID &= ~(255);
        saveRAM->playerID |= 1 << Mod_UISaveSlot->subSelection;
        SetCharacterFlags();
        ExitSubMenu();
    }
    else if (backPress) {
        ExitSubMenu();
    }
}

void UISaveSlot_EditState_EncoreSidekick(void)
{
    RSDK_THIS(UISaveSlot);

    int8 optionCount = 3;
    if (API.CheckDLC(DLC_PLUS))
        optionCount += 2;

    UISaveSlot_HandleUpDown(optionCount);

    if (confirmPress) {
        GetSaveRAMPointer();
        saveRAM->playerID &= ~(255 << 8);
        if (Mod_UISaveSlot->subSelection)
            saveRAM->playerID |= (1 << (Mod_UISaveSlot->subSelection - 1)) << 8;
        SetCharacterFlags();
        ExitSubMenu();
    }
    else if (backPress) {
        ExitSubMenu();
    }
}

void UISaveSlot_EditState_EncoreStock(void)
{
    RSDK_THIS(UISaveSlot);

    int8 optionCount = 3;
    if (API.CheckDLC(DLC_PLUS))
        optionCount += 2;

    int8 stock = Mod_UISaveSlot->menuOptions[Mod_UISaveSlot->mainSelection] - SAVEEDITOR_STOCK1;

    UISaveSlot_HandleUpDown(optionCount);

    if (confirmPress) {
        GetSaveRAMPointer();
        saveRAM->stock &= ~(255 << (8 * stock));
        if (Mod_UISaveSlot->subSelection)
            saveRAM->stock |= (1 << (Mod_UISaveSlot->subSelection - 1)) << (8 * stock);
        SetCharacterFlags();
        ExitSubMenu();
    }
    else if (backPress) {
        ExitSubMenu();
    }
}
#endif

void UISaveSlot_EditState_Zone(void)
{
    RSDK_THIS(UISaveSlot);

    UISaveSlot_HandleUpDown(ZONE_COUNT_SAVEFILE - 1);

    if (confirmPress) {
        GetSaveRAMPointer();
        if (Mod_UISaveSlot->subSelection != saveRAM->zoneID) {
            saveRAM->zoneID = Mod_UISaveSlot->subSelection;
            if (saveRAM->zoneID >= ZONE_ERZ) {
                saveRAM->saveState = SAVEGAME_COMPLETE;
                saveRAM->zoneID    = ZONE_ERZ;
                self->state        = Mod.GetPublicFunction(NULL, "UISaveSlot_State_CompletedSave");
            }
            else {
                saveRAM->saveState = SAVEGAME_INPROGRESS;
                self->state        = Mod.GetPublicFunction(NULL, "UISaveSlot_State_ActiveSave");
            }
            saveRAM->collectedSpecialRings = 0;
        }

        // Workaround for zone palettes not being applied after initializing a new save
        // Setting currentlySelected to true when initializing it just breaks the whole menu. todo: find a proper fix
        bool32 selectedStore    = self->currentlySelected;
        self->currentlySelected = true;
        ExitSubMenu();
        self->currentlySelected = selectedStore;
    }
    else if (backPress) {
        ExitSubMenu();
    }
}

void UISaveSlot_EditState_SetLives(void)
{
    RSDK_THIS(UISaveSlot);

    UISaveSlot_HandleSetValue(1, 99);

    if (confirmPress) {
        GetSaveRAMPointer();
        saveRAM->lives = Mod_UISaveSlot->customValue;
        ExitSubMenu();
    }
    else if (backPress) {
        ExitSubMenu();
    }
}

#if MANIA_USE_PLUS
void UISaveSlot_EditState_SetContinues(void)
{
    RSDK_THIS(UISaveSlot);

    UISaveSlot_HandleSetValue(0, 99);

    if (confirmPress) {
        GetSaveRAMPointer();
        saveRAM->continues = Mod_UISaveSlot->customValue;
        ExitSubMenu();
    }
    else if (backPress) {
        ExitSubMenu();
    }
}
#endif

void UISaveSlot_EditState_SetScore(void)
{
    RSDK_THIS(UISaveSlot);

    UISaveSlot_HandleSetValue(0, 9999999);

    if (confirmPress) {
        GetSaveRAMPointer();
        if (Mod_UISaveSlot->customValue != saveRAM->score) {
            saveRAM->score    = Mod_UISaveSlot->customValue;
            saveRAM->score1UP = (Mod_UISaveSlot->customValue / 50000) * 50000 + 50000;
        }
        ExitSubMenu();
    }
    else if (backPress) {
        ExitSubMenu();
    }
}

void UISaveSlot_EditState_Emeralds(void)
{
    RSDK_THIS(UISaveSlot);

    if (ControllerInfo[CONT_P1].keyRight.press) {
        if (++Mod_UISaveSlot->subSelection > 6)
            Mod_UISaveSlot->subSelection = 0;
    }
    else if (ControllerInfo[CONT_P1].keyLeft.press) {
        if (--Mod_UISaveSlot->subSelection < 0)
            Mod_UISaveSlot->subSelection = 6;
    }
    else if (ControllerInfo[CONT_P1].keyUp.press || ControllerInfo[CONT_P1].keyDown.press)
        SET_BIT(Mod_UISaveSlot->customValue, !GET_BIT(Mod_UISaveSlot->customValue, Mod_UISaveSlot->subSelection), Mod_UISaveSlot->subSelection);

    if (confirmPress) {
        GetSaveRAMPointer();
        if (Mod_UISaveSlot->customValue != saveRAM->collectedEmeralds) {
            saveRAM->collectedEmeralds = Mod_UISaveSlot->customValue;
            saveRAM->nextSpecialStage  = 0;
            for (int8 e = 0; e < 7; e++) {
                if (!GET_BIT(saveRAM->collectedEmeralds, e)) {
                    saveRAM->nextSpecialStage = e;
                    break;
                }
            }
        }
        ExitSubMenu();
    }
    else if (backPress) {
        ExitSubMenu();
    }
}

void UISaveSlot_EditState_Wait(void) {}

void UISaveSlot_InitDLG_CB(void)
{
    ObjectUIDialog *UIDialog = Mod.FindObject("UIDialog");
    EntityUIDialog *dialog   = (EntityUIDialog *)UIDialog->activeDialog;
    EntityUISaveSlot *self   = (EntityUISaveSlot *)dialog->entityPtr;

    dialog->parent->state = StateMachine_None;

    UIWaitSpinner_StartWait();

    GetSaveRAMPointer();

    saveRAM->saveState             = SAVEGAME_INPROGRESS;
    saveRAM->zoneID                = 0;
    saveRAM->lives                 = 3;
    saveRAM->collectedEmeralds     = 0b0000000;
    saveRAM->continues             = 0;
    saveRAM->score                 = 0;
    saveRAM->score1UP              = 500000;
    saveRAM->collectedSpecialRings = 0;
    saveRAM->nextSpecialStage      = 0;
#if MANIA_USE_PLUS
    saveRAM->characterID = !self->encoreMode ? self->frameID : 0;
    if (self->encoreMode) {
        saveRAM->playerID = ID_SONIC | ID_MIGHTY << 8;
        saveRAM->stock    = ID_NONE;
    }
#else
    saveRAM->characterID = self->frameID;
#endif

    SaveGame_SaveFile(UISaveSlot_InitSaveCB);
}

#if MANIA_USE_PLUS
void UISaveSlot_InitSaveCB(bool32 success)
#else
void UISaveSlot_InitSaveCB(void)
#endif
{
    ObjectUIDialog *UIDialog   = Mod.FindObject("UIDialog");
    EntityUIDialog *dialog     = (EntityUIDialog *)UIDialog->activeDialog;
    EntityUISaveSlot *saveSlot = (EntityUISaveSlot *)dialog->entityPtr;
    saveSlot->state            = Mod.GetPublicFunction(NULL, "UISaveSlot_State_ActiveSave");
#if MANIA_USE_PLUS
    saveSlot->stateInput = StateMachine_None;
#endif
    saveSlot->isSelected = true;
    UIWaitSpinner_FinishWait();
    UIDialog_CloseOnSel_HandleSelection(dialog, StateMachine_None);

    Entity *storeEntity = SceneInfo->entity;
    SceneInfo->entity   = (Entity *)saveSlot;
    UISaveSlot_LoadSaveInfo();
    UISaveSlot_SetupEditor();
    SceneInfo->entity = storeEntity;
}

void UISaveSlot_CloseEditor_CB(void)
{
    UIWaitSpinner_StartWait();
    SaveGame_SaveFile(UISaveSlot_Edit_ExitCB);
    Mod_UISaveSlot->state = UISaveSlot_EditState_Wait;
}

#if MANIA_USE_PLUS
void UISaveSlot_Edit_ExitCB(bool32 success)
#else
void UISaveSlot_Edit_ExitCB(void)
#endif
{
    RSDK_THIS(UISaveSlot);

    UIWaitSpinner_FinishWait();
    EntityUIControl *control = (EntityUIControl *)self->parent;
    self->processButtonCB    = Mod_UISaveSlot->processButtonCBStore;
    control->backPressCB     = Mod_UISaveSlot->backPressCBStore;
    control->yPressCB        = Mod_UISaveSlot->yPressCBStore;
#if MANIA_USE_PLUS
    self->stateInput = Mod_UISaveSlot->stateInputStore;
#endif
    Mod_UISaveSlot->state = StateMachine_None;
}

bool32 UISaveSlot_Edit_BackCB(void) { return false; }

void UISaveSlot_EditState_DrawChar(void)
{
    int8 characterCount = 3;
#if MANIA_USE_PLUS
    if (API.CheckDLC(DLC_PLUS))
        characterCount += 2;

    int8 optionCount = characterCount + (Mod_UISaveSlot->state != UISaveSlot_EditState_EncoreLeader);
#else
    int8 optionCount = characterCount + 1;
#endif

    ObjectUIBackground *UIBackground = Mod.FindObject("UIBackground");
    RSDK.DrawRect(SUBBOX_XPOS, BOX_YPOS, 110, BOX_HEIGHT(optionCount), UIBackground->activeColors[2], 0xFF, INK_NONE, true);

    Vector2 drawPos;

    // Draw Selection Arrow
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 8);
    drawPos.y = TO_FIXED(BOX_YPOS + 9 + (Mod_UISaveSlot->subSelection * OPTION_SPACING));

    Mod_UISaveSlot->animator.frameID = 30; // >
    RSDK.DrawSprite(&Mod_UISaveSlot->animator, &drawPos, true);

    // Initialize Option Text Position
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 16);
    drawPos.y = TO_FIXED(BOX_YPOS + 9);

    // Draw Option Text
    if (Mod_UISaveSlot->state == UISaveSlot_EditState_ManiaChar) {
        DrawOptionText(&Mod_UISaveSlot->charStrings[CHARACTER_SONIC_TAILS]);
    }
#if MANIA_USE_PLUS
    else if (Mod_UISaveSlot->state == UISaveSlot_EditState_EncoreSidekick || Mod_UISaveSlot->state == UISaveSlot_EditState_EncoreStock) {
        DrawOptionText(&Mod_UISaveSlot->charStrings[CHARACTER_NONE]);
    }
#endif
    for (uint8 s = CHARACTER_SONIC; s < CHARACTER_SONIC + characterCount; s++) {
        DrawOptionText(&Mod_UISaveSlot->charStrings[s]);
    }
}

void UISaveSlot_EditState_DrawZone(void)
{
    ObjectUIBackground *UIBackground = Mod.FindObject("UIBackground");
    RSDK.DrawRect(SUBBOX_XPOS, BOX_YPOS, 150, BOX_HEIGHT(ZONE_COUNT_SAVEFILE), UIBackground->activeColors[2], 0xFF, INK_NONE, true);

    Vector2 drawPos;

    // Draw Selection Arrow
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 8);
    drawPos.y = TO_FIXED(BOX_YPOS + 9 + (Mod_UISaveSlot->subSelection * OPTION_SPACING));

    Mod_UISaveSlot->animator.frameID = 30; // >
    RSDK.DrawSprite(&Mod_UISaveSlot->animator, &drawPos, true);

    // Initialize Option Text Position
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 16);
    drawPos.y = TO_FIXED(BOX_YPOS + 9);

    // Draw Option Text
    for (uint8 s = ZONE_GHZ; s < ZONE_COUNT_SAVEFILE; s++) {
        DrawOptionText(&Mod_UISaveSlot->zoneStrings[s]);
    }
}

void UISaveSlot_EditState_DrawSetValue(void)
{
    ObjectUIBackground *UIBackground = Mod.FindObject("UIBackground");
    RSDK.DrawRect(SUBBOX_XPOS, BOX_YPOS, (Mod_UISaveSlot->valueDigits * 8) + 11, BOX_HEIGHT(3), UIBackground->activeColors[2], 0xFF, INK_NONE, true);

    Vector2 drawPos;

    // Draw Plus Sign
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 9 + (Mod_UISaveSlot->subSelection * 8));
    drawPos.y = TO_FIXED(BOX_YPOS + 9);

    Mod_UISaveSlot->animator.frameID = 11; // +
    RSDK.DrawSprite(&Mod_UISaveSlot->animator, &drawPos, true);

    // Initialize Number Position
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 1 + (Mod_UISaveSlot->valueDigits * 8));
    drawPos.y += TO_FIXED(OPTION_SPACING);

    // Draw Number
    int32 digitCount = Mod_UISaveSlot->valueDigits;
    int32 digit      = 1;
    while (digitCount--) {
        int32 digitNumber                = Mod_UISaveSlot->customValue / digit % 10;
        Mod_UISaveSlot->animator.frameID = 16 + digitNumber;
        if (digitNumber == 6 || digitNumber == 7)
            drawPos.x -= TO_FIXED(1);
        RSDK.DrawSprite(&Mod_UISaveSlot->animator, &drawPos, true);
        digit *= 10;
        drawPos.x -= TO_FIXED(8);
        if (digitNumber == 6 || digitNumber == 7)
            drawPos.x += TO_FIXED(1);
    }

    // Draw Minus Sign
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 9 + (Mod_UISaveSlot->subSelection * 8));
    drawPos.y += TO_FIXED(OPTION_SPACING);

    Mod_UISaveSlot->animator.frameID = 13; // -
    RSDK.DrawSprite(&Mod_UISaveSlot->animator, &drawPos, true);
}

void UISaveSlot_EditState_DrawEmeralds(void)
{
    ObjectUIBackground *UIBackground = Mod.FindObject("UIBackground");
    RSDK.DrawRect(SUBBOX_XPOS, BOX_YPOS, 92, BOX_HEIGHT(3), UIBackground->activeColors[2], 0xFF, INK_NONE, true);

    Vector2 drawPos;

    // Draw Plus Sign
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 9 + (Mod_UISaveSlot->subSelection * 12));
    drawPos.y = TO_FIXED(BOX_YPOS + 9);

    Mod_UISaveSlot->animator.frameID = 11; // +
    RSDK.DrawSprite(&Mod_UISaveSlot->animator, &drawPos, true);

    // Initialize Emeralds Position
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 9);
    drawPos.y += TO_FIXED(OPTION_SPACING + 2);

    // Draw Emeralds
    for (int8 e = 0; e < 7; e++) {
        Mod_UISaveSlot->emeraldsAnimator.frameID = GET_BIT(Mod_UISaveSlot->customValue, e) ? e : 7;
        if (Mod_UISaveSlot->emeraldsAnimator.frameID == 7)
            drawPos.y -= TO_FIXED(1);
        RSDK.DrawSprite(&Mod_UISaveSlot->emeraldsAnimator, &drawPos, true);
        drawPos.x += TO_FIXED(12);
        if (Mod_UISaveSlot->emeraldsAnimator.frameID == 7)
            drawPos.y += TO_FIXED(1);
    }

    // Draw Minus Sign
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 9 + (Mod_UISaveSlot->subSelection * 12));
    drawPos.y += TO_FIXED(OPTION_SPACING);

    Mod_UISaveSlot->animator.frameID = 13; // -
    RSDK.DrawSprite(&Mod_UISaveSlot->animator, &drawPos, true);
}

void UISaveSlot_HandleTouchControls(void)
{
    RSDKControllerState *controller = &ControllerInfo[CONT_P1];

    bool32 touchedUp = false;
    if (UISaveSlot_CheckTouchRect(0, 0, ScreenInfo->center.x, Y_THIRD)) {
        ControllerInfo->keyUp.down |= true;
        controller->keyUp.down = true;
        touchedUp              = true;
    }

    bool32 touchedDown = false;
    if (UISaveSlot_CheckTouchRect(0, Y_THIRD * 2, ScreenInfo->center.x, ScreenInfo->size.y)) {
        ControllerInfo->keyDown.down |= true;
        controller->keyDown.down = true;
        touchedDown              = true;
    }

    bool32 touchedLeft = false;
    if (UISaveSlot_CheckTouchRect(0, Y_THIRD, ScreenInfo->center.x / 2, Y_THIRD * 2)) {
        ControllerInfo->keyLeft.down |= true;
        controller->keyLeft.down = true;
        touchedLeft              = true;
    }

    bool32 touchedRight = false;
    if (UISaveSlot_CheckTouchRect(ScreenInfo->center.x / 2, Y_THIRD, ScreenInfo->center.x, Y_THIRD * 2)) {
        ControllerInfo->keyRight.down |= true;
        controller->keyRight.down = true;
        touchedRight              = true;
    }

    bool32 touchedConfirm = false;
    if (UISaveSlot_CheckTouchRect(ScreenInfo->center.x, ScreenInfo->center.y, ScreenInfo->size.x, ScreenInfo->size.y)) {
        ControllerInfo->keyStart.down |= true;
        controller->keyStart.down = true;
        touchedConfirm            = true;
    }

    bool32 touchedBack = false;
    if (UISaveSlot_CheckTouchRect(ScreenInfo->center.x, 0, ScreenInfo->size.x, ScreenInfo->center.y)) {
        if (API_GetConfirmButtonFlip()) {
            ControllerInfo->keyA.down |= true;
            controller->keyA.down = true;
        }
        else {
            ControllerInfo->keyB.down |= true;
            controller->keyB.down = true;
        }
        touchedBack = true;
    }

    if (!Mod_UISaveSlot->touchUp && touchedUp) {
        ControllerInfo->keyUp.press |= ControllerInfo->keyUp.down;
        controller->keyUp.press |= controller->keyUp.down;
    }
    Mod_UISaveSlot->touchUp = controller->keyUp.down;

    if (!Mod_UISaveSlot->touchDown && touchedDown) {
        ControllerInfo->keyDown.press |= ControllerInfo->keyDown.down;
        controller->keyDown.press |= controller->keyDown.down;
    }
    Mod_UISaveSlot->touchDown = controller->keyDown.down;

    if (!Mod_UISaveSlot->touchLeft && touchedLeft) {
        ControllerInfo->keyLeft.press |= ControllerInfo->keyLeft.down;
        controller->keyLeft.press |= controller->keyLeft.down;
    }
    Mod_UISaveSlot->touchLeft = controller->keyLeft.down;

    if (!Mod_UISaveSlot->touchRight && touchedRight) {
        ControllerInfo->keyRight.press |= ControllerInfo->keyRight.down;
        controller->keyRight.press |= controller->keyRight.down;
    }
    Mod_UISaveSlot->touchRight = controller->keyRight.down;

    if (!Mod_UISaveSlot->touchConfirm && touchedConfirm) {
        ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
        controller->keyStart.press |= controller->keyStart.down;
    }
    Mod_UISaveSlot->touchConfirm = controller->keyStart.down;

    if (!Mod_UISaveSlot->touchBack && touchedBack) {
        if (API_GetConfirmButtonFlip()) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        else {
            ControllerInfo->keyB.press |= ControllerInfo->keyB.down;
            controller->keyB.press |= controller->keyB.down;
        }
    }
    Mod_UISaveSlot->touchBack = API_GetConfirmButtonFlip() ? controller->keyA.down : controller->keyB.down;
}

bool32 UISaveSlot_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2)
{
    for (int32 t = 0; t < TouchInfo->count; ++t) {
        int32 tx = (int32)(TouchInfo->x[t] * ScreenInfo->size.x);
        int32 ty = (int32)(TouchInfo->y[t] * ScreenInfo->size.y);

        if (TouchInfo->down[t]) {
            if (tx >= x1 && ty >= y1 && tx <= x2 && ty <= y2) {
                return true;
            }
        }
    }

    return false;
}

void UISaveSlot_HandleUpDown(int8 maxCount)
{
    if (Mod_UISaveSlot->state == UISaveSlot_EditState_Main) {
        if (ControllerInfo[CONT_P1].keyDown.press) {
            if (++Mod_UISaveSlot->mainSelection > maxCount)
                Mod_UISaveSlot->mainSelection = 0;
        }
        else if (ControllerInfo[CONT_P1].keyUp.press) {
            if (--Mod_UISaveSlot->mainSelection < 0)
                Mod_UISaveSlot->mainSelection = maxCount;
        }
    }
    else {
        if (ControllerInfo[CONT_P1].keyDown.press) {
            if (++Mod_UISaveSlot->subSelection > maxCount)
                Mod_UISaveSlot->subSelection = 0;
        }
        else if (ControllerInfo[CONT_P1].keyUp.press) {
            if (--Mod_UISaveSlot->subSelection < 0)
                Mod_UISaveSlot->subSelection = maxCount;
        }
    }
}

void UISaveSlot_HandleSetValue(int32 minValue, int32 maxValue)
{
    if (ControllerInfo[CONT_P1].keyRight.press) {
        if (++Mod_UISaveSlot->subSelection >= Mod_UISaveSlot->valueDigits)
            Mod_UISaveSlot->subSelection = 0;
    }
    else if (ControllerInfo[CONT_P1].keyLeft.press) {
        if (--Mod_UISaveSlot->subSelection < 0)
            Mod_UISaveSlot->subSelection = Mod_UISaveSlot->valueDigits - 1;
    }
    else if (ControllerInfo[CONT_P1].keyUp.press) {
        int32 digit    = Mod_UISaveSlot->valueDigits;
        int32 decrease = 1;
        while (--digit > Mod_UISaveSlot->subSelection) decrease *= 10;
        Mod_UISaveSlot->customValue += decrease;
        if (Mod_UISaveSlot->customValue > maxValue)
            Mod_UISaveSlot->customValue -= maxValue - minValue + 1;
    }
    else if (ControllerInfo[CONT_P1].keyDown.press) {
        int32 digit    = Mod_UISaveSlot->valueDigits;
        int32 decrease = 1;
        while (--digit > Mod_UISaveSlot->subSelection) decrease *= 10;
        Mod_UISaveSlot->customValue -= decrease;
        if (Mod_UISaveSlot->customValue < minValue)
            Mod_UISaveSlot->customValue += maxValue - minValue + 1;
    }
}
