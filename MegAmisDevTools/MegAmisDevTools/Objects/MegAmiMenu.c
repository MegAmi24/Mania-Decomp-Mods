// ---------------------------------------------------------------------
// RSDK Project: MegAmi's Dev Tools
// Original Game: Sonic Mania
// Object Description: MegAmiMenu Object
// Object Author: MegAmi
// ---------------------------------------------------------------------

#include "GameAPI/Game.h"
#include "MegAmiMenu.h"
#include "Player.h"
#include "Misc.h"

ObjectMegAmiMenu *MegAmiMenu;

void MegAmiMenu_Update(void)
{
    RSDK_THIS(MegAmiMenu);

    if (SceneInfo->state != ENGINESTATE_FROZEN)
        RSDK.SetEngineState(ENGINESTATE_FROZEN);

    EntityPlayer *player = (EntityPlayer *)self->parent;
    if (player->classID != Player->classID || ControllerInfo[player->controllerID].keySelect.press)
        destroyEntity(self);
    else {
        MegAmiMenu_HandleTouchControls();
        StateMachine_Run(self->state);
    }

    // Return to gameplay if the menu is closed
    if (self->classID != MegAmiMenu->classID)
        RSDK.SetEngineState(ENGINESTATE_REGULAR);
}

void MegAmiMenu_LateUpdate(void) {}

void MegAmiMenu_StaticUpdate(void) {}

void MegAmiMenu_Draw(void)
{
    RSDK_THIS(MegAmiMenu);

    if (RSDK.GetEntitySlot(self->parent) == RSDK.GetEntitySlot(RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player))) {
        RSDK.DrawRect(MAINBOX_XPOS, BOX_YPOS, self->mainBoxWidth, BOX_HEIGHT(self->menuCount + 1), BOX_COLOR, 0xFF, INK_NONE, true);

        Vector2 drawPos;

        // Draw Selection Arrow
        drawPos.x = TO_FIXED(MAINBOX_XPOS + 8);
        drawPos.y = TO_FIXED(BOX_YPOS + 9 + (self->mainSelection * OPTION_SPACING));

        self->animator.frameID = 30; // >
        RSDK.DrawSprite(&self->animator, &drawPos, true);

        // Initialize Option Text Position
        drawPos.x = TO_FIXED(MAINBOX_XPOS + 16);
        drawPos.y = TO_FIXED(BOX_YPOS + 9);

        // Draw Option Text
        for (uint8 s = 0; s <= self->menuCount; s++) {
            DrawOptionText(&self->menuStrings[s]);
        }

        if (self->stateDraw) {
            RSDK.DrawRect(MAINBOX_XPOS, BOX_YPOS, self->mainBoxWidth, BOX_HEIGHT(self->menuCount + 1), 0x000000, 0x80, INK_ALPHA, true);
            StateMachine_Run(self->stateDraw);
        }
    }
}

void MegAmiMenu_Create(void *data)
{
    RSDK_THIS(MegAmiMenu);

    ObjectUIWidgets *UIWidgets = Mod.FindObject("UIWidgets");

    RSDK.SetSpriteAnimation(UIWidgets->fontFrames, 0, &self->animator, true, 0);

    if (!SceneInfo->inEditor) {
        ObjectZone *Zone = Mod.FindObject("Zone");

        self->active    = ACTIVE_ALWAYS;
        self->visible   = true;
        self->drawGroup = Zone->hudDrawGroup;

        self->parent         = (Entity *)data;
        EntityPlayer *player = (EntityPlayer *)self->parent;

        self->menuCount = -1;

        // Initialize Options
        AddMenuOption(MEGAMIMENU_P1CHAR, "CHANGE CHARACTER");
        if (!player->sidekick && globals->gameMode != MODE_COMPETITION) {
            AddMenuOption(MEGAMIMENU_P2CHAR, "CHANGE SIDEKICK");
        }
#if MANIA_USE_PLUS
        if (globals->gameMode == MODE_ENCORE) {
            AddMenuOption(MEGAMIMENU_STOCK1, "CHANGE STOCK 1");
            AddMenuOption(MEGAMIMENU_STOCK2, "CHANGE STOCK 2");
            AddMenuOption(MEGAMIMENU_STOCK3, "CHANGE STOCK 3");
        }
#endif
        AddMenuOption(MEGAMIMENU_SHIELD, "CHANGE SHIELD");
        AddMenuOption(MEGAMIMENU_SHOES, "GIVE SPEED SHOES");
        AddMenuOption(MEGAMIMENU_SETRINGS, "SET RING COUNT");
        AddMenuOption(MEGAMIMENU_HYPERRING, !player->hyperRing ? "GIVE HYPER RING" : "REMOVE HYPER RING");
        AddMenuOption(MEGAMIMENU_SUPER, player->superState != SUPERSTATE_SUPER ? "TURN SUPER" : "REVERT SUPER");
        AddMenuOption(MEGAMIMENU_INVINCIBILITY, !MegAmiMenu->playerInv[player->playerID] ? "ENABLE INVINCIBILITY" : "DISABLE INVINCIBILITY");
        AddMenuOption(MEGAMIMENU_EXIT, "EXIT");

        for (uint8 s = 0; s <= self->menuCount; s++) RSDK.SetSpriteString(UIWidgets->fontFrames, 0, &self->menuStrings[s]);

        self->mainBoxWidth = 0;
        for (uint8 s = 0; s <= self->menuCount; s++) {
            int32 stringWidth = RSDK.GetStringWidth(UIWidgets->fontFrames, 0, &self->menuStrings[s], 0, &self->menuStrings[s].length, 0);
            if (stringWidth > self->mainBoxWidth)
                self->mainBoxWidth = stringWidth;
        }
        self->mainBoxWidth += 19;

        self->state     = MegAmiMenu_State_Main;
        self->stateDraw = StateMachine_None;

        MegAmiMenu->touchUp      = false;
        MegAmiMenu->touchDown    = false;
        MegAmiMenu->touchLeft    = false;
        MegAmiMenu->touchRight   = false;
        MegAmiMenu->touchConfirm = false;
        MegAmiMenu->touchBack    = false;

        RSDK.SetEngineState(ENGINESTATE_FROZEN);
    }
    else {
        RSDK.InitString(&self->menuStrings[0], "MEGAMI MENU", false);
        RSDK.SetSpriteString(UIWidgets->fontFrames, 0, &self->menuStrings[0]);
    }
}

void MegAmiMenu_StageLoad(void)
{
    ObjectUIWidgets *UIWidgets = Mod.FindObject("UIWidgets");

    // Initialize Character Strings
    RSDK.InitString(&MegAmiMenu->charStrings[CHARACTER_NONE], "NONE", false);
    RSDK.InitString(&MegAmiMenu->charStrings[CHARACTER_SONIC], "SONIC", false);
    RSDK.InitString(&MegAmiMenu->charStrings[CHARACTER_TAILS], "TAILS", false);
    RSDK.InitString(&MegAmiMenu->charStrings[CHARACTER_KNUCKLES], "KNUCKLES", false);
#if MANIA_USE_PLUS
    RSDK.InitString(&MegAmiMenu->charStrings[CHARACTER_MIGHTY], "MIGHTY", false);
    RSDK.InitString(&MegAmiMenu->charStrings[CHARACTER_RAY], "RAY", false);
#endif

    // Initialize Shield Strings
    RSDK.InitString(&MegAmiMenu->shieldStrings[SHIELD_NONE], "NONE", false);
    RSDK.InitString(&MegAmiMenu->shieldStrings[SHIELD_BLUE], "BLUE", false);
    RSDK.InitString(&MegAmiMenu->shieldStrings[SHIELD_BUBBLE], "BUBBLE", false);
    RSDK.InitString(&MegAmiMenu->shieldStrings[SHIELD_FIRE], "FIRE", false);
    RSDK.InitString(&MegAmiMenu->shieldStrings[SHIELD_LIGHTNING], "LIGHTNING", false);

    for (uint8 c = 0; c < CHARACTER_COUNT; c++) RSDK.SetSpriteString(UIWidgets->fontFrames, 0, &MegAmiMenu->charStrings[c]);
    for (uint8 s = 0; s < SHIELD_COUNT; s++) RSDK.SetSpriteString(UIWidgets->fontFrames, 0, &MegAmiMenu->shieldStrings[s]);
}

void MegAmiMenu_State_Main(void)
{
    RSDK_THIS(MegAmiMenu);

    EntityPlayer *player = (EntityPlayer *)self->parent;

    MegAmiMenu_HandleUpDown(ControllerInfo[player->controllerID], self->menuCount);

    if (confirmPress) {
        switch (selectedOption) {
            default: break;
            case MEGAMIMENU_P1CHAR:
                self->state        = MegAmiMenu_State_P1Char;
                self->stateDraw    = MegAmiMenu_State_DrawChar;
                self->subSelection = 0;
                break;
            case MEGAMIMENU_P2CHAR:
                self->state        = MegAmiMenu_State_P2Char;
                self->stateDraw    = MegAmiMenu_State_DrawChar;
                self->subSelection = 0;
                break;
#if MANIA_USE_PLUS
            case MEGAMIMENU_STOCK1:
            case MEGAMIMENU_STOCK2:
            case MEGAMIMENU_STOCK3:
                self->state        = MegAmiMenu_State_EncoreStock;
                self->stateDraw    = MegAmiMenu_State_DrawChar;
                self->subSelection = 0;
                break;
#endif
            case MEGAMIMENU_SHIELD:
                self->state        = MegAmiMenu_State_Shield;
                self->stateDraw    = MegAmiMenu_State_DrawShield;
                self->subSelection = 0;
                break;
            case MEGAMIMENU_SHOES:
                player->speedShoesTimer = 1320;
                Player_UpdatePhysicsState(player);
                if (player->superState == SUPERSTATE_NONE) {
                    Music_PlayJingle(TRACK_SNEAKERS);
                    ObjectImageTrail *ImageTrail = Mod.FindObject("ImageTrail");
                    EntityImageTrail *powerup    = RSDK_GET_ENTITY(2 * Player->playerCount + RSDK.GetEntitySlot(player), ImageTrail);
                    RSDK.ResetEntity(powerup, ImageTrail->classID, player);
                }
                destroyEntity(self);
                break;
            case MEGAMIMENU_SETRINGS:
                self->state        = MegAmiMenu_State_SetRings;
                self->stateDraw    = MegAmiMenu_State_DrawSetValue;
                self->subSelection = 0;
                self->customValue  = player->rings;
                self->valueDigits  = 3;
                break;
            case MEGAMIMENU_HYPERRING:
                player->hyperRing ^= true;
                destroyEntity(self);
                break;
            case MEGAMIMENU_SUPER:
                if (player->superState == SUPERSTATE_NONE) {
                    Player_GiveRings(player, 50, false);
                    Player_TryTransform(player, 0x7F);
                }
                else
                    player->superState = SUPERSTATE_FADEOUT;
                destroyEntity(self);
                break;
            case MEGAMIMENU_INVINCIBILITY:
                MegAmiMenu->playerInv[player->playerID] ^= true;
                destroyEntity(self);
                break;
            case MEGAMIMENU_EXIT: destroyEntity(self); break;
        }
    }
    else if (backPress)
        destroyEntity(self);
}

void MegAmiMenu_State_P1Char(void)
{
    RSDK_THIS(MegAmiMenu);

    EntityPlayer *player = (EntityPlayer *)self->parent;

    int8 optionCount = 2;
#if MANIA_USE_PLUS
    if (API.CheckDLC(DLC_PLUS))
        optionCount += 2;
#endif

    MegAmiMenu_HandleUpDown(ControllerInfo[player->controllerID], optionCount);

    if (confirmPress) {
        Player_ChangeCharacter(player, 1 << self->subSelection);
#if MANIA_USE_PLUS
        if (globals->gameMode == MODE_ENCORE) {
            SetCharacterFlags();
        }
#endif
        destroyEntity(self);
    }
    else if (backPress) {
        self->state     = MegAmiMenu_State_Main;
        self->stateDraw = StateMachine_None;
    }
}

void MegAmiMenu_State_P2Char(void)
{
    RSDK_THIS(MegAmiMenu);

    EntityPlayer *player = (EntityPlayer *)self->parent;

    int8 optionCount = 3;
#if MANIA_USE_PLUS
    if (API.CheckDLC(DLC_PLUS))
        optionCount += 2;
#endif

    MegAmiMenu_HandleUpDown(ControllerInfo[player->controllerID], optionCount);

    if (confirmPress) {
        EntityPlayer *sidekick = RSDK_GET_ENTITY(RSDK.GetEntitySlot(player) + 1, Player);
        if (sidekick->classID == Player->classID) {
            if (self->subSelection == CHARACTER_NONE) {
                // Get rid of P2
                Player_ChangeCharacter(sidekick, ID_NONE);
                destroyEntity(sidekick);

                // Handle new player count
                Entity *powerup1 = RSDK_GET_ENTITY_GEN(RSDK.GetEntitySlot(player) + Player->playerCount);
                Entity *powerup2 = RSDK_GET_ENTITY_GEN(2 * Player->playerCount + RSDK.GetEntitySlot(player));
#if MANIA_USE_PLUS
                Player->playerCount = globals->gameMode == MODE_ENCORE ? 2 : RSDK.GetEntityCount(Player->classID, false);
#else
                Player->playerCount = RSDK.GetEntityCount(Player->classID, false);
#endif
                if (powerup1->classID)
                    RSDK.CopyEntity(RSDK_GET_ENTITY_GEN(RSDK.GetEntitySlot(player) + Player->playerCount), powerup1, true);
                if (powerup2->classID)
                    RSDK.CopyEntity(RSDK_GET_ENTITY_GEN(2 * Player->playerCount + RSDK.GetEntitySlot(player)), powerup2, true);
            }
            else
                Player_ChangeCharacter(sidekick, 1 << (self->subSelection - 1)); // P2 already exists, just change the character
        }
        else if (self->subSelection != CHARACTER_NONE) {
            // P2 doesn't exist, spawn them
            Entity *powerup2 = RSDK_GET_ENTITY_GEN(2 * Player->playerCount + RSDK.GetEntitySlot(player));
            if (powerup2->classID)
                RSDK.CopyEntity(RSDK_GET_ENTITY_GEN(RSDK.GetEntitySlot(powerup2) + 2), powerup2, true);

            if (sidekick->classID) // If this is a powerup
                RSDK.CopyEntity(RSDK_GET_ENTITY_GEN(RSDK.GetEntitySlot(sidekick) + 1), sidekick, false);
            destroyEntity(sidekick);

            sidekick->classID   = Player->classID;
            Player->jumpInTimer = 0;
            sidekick->playerID  = 1;

            ObjectDust *Dust  = Mod.FindObject("Dust");
            EntityDust *dust  = CREATE_ENTITY(Dust, INT_TO_VOID(1), player->position.x, player->position.y);
            dust->visible     = false;
            dust->active      = ACTIVE_NEVER;
            dust->isPermanent = true;
            dust->position.y  = TO_FIXED(ScreenInfo->position.y - 128);

            ObjectZone *Zone = Mod.FindObject("Zone");
            Player_ChangeCharacter(sidekick, 1 << (self->subSelection - 1));
            sidekick->velocity.x       = 0;
            sidekick->velocity.y       = 0;
            sidekick->groundVel        = 0;
            sidekick->position.x       = -TO_FIXED(64);
            sidekick->position.y       = -TO_FIXED(64);
            sidekick->camera           = NULL;
            sidekick->angle            = 0x80;
            sidekick->state            = Mod.GetPublicFunction(NULL, "Player_State_HoldRespawn");
            sidekick->abilityPtrs[0]   = dust;
            sidekick->abilityValues[0] = 0;
            sidekick->nextAirState     = StateMachine_None;
            sidekick->nextGroundState  = StateMachine_None;
            sidekick->stateInput       = Mod.GetPublicFunction(NULL, "Player_Input_P2_Delay");
            sidekick->position.x       = -0x400000;
            sidekick->position.y       = -0x400000;
            sidekick->velocity.x       = 0;
            sidekick->velocity.y       = 0;
            sidekick->groundVel        = 0;
            sidekick->tileCollisions   = TILECOLLISION_NONE;
            sidekick->interaction      = false;
            sidekick->drawGroup        = Zone->playerDrawGroup[1];
            sidekick->drownTimer       = 0;
            sidekick->active           = ACTIVE_NORMAL;
            sidekick->collisionPlane   = 0;
            sidekick->collisionMode    = CMODE_FLOOR;
            sidekick->collisionLayers  = Zone->collisionLayers;
            sidekick->controllerID     = CONT_P2;
            sidekick->sidekick         = true;
            sidekick->drawFX           = FX_FLIP | FX_ROTATE;
            sidekick->visible          = true;

#if MANIA_USE_PLUS
            Player->playerCount = globals->gameMode == MODE_ENCORE ? 2 : RSDK.GetEntityCount(Player->classID, false);
#else
            Player->playerCount = RSDK.GetEntityCount(Player->classID, false);
#endif
        }
#if MANIA_USE_PLUS
        if (globals->gameMode == MODE_ENCORE) {
            SetCharacterFlags();
        }
#endif
        destroyEntity(self);
    }
    else if (backPress) {
        self->state     = MegAmiMenu_State_Main;
        self->stateDraw = StateMachine_None;
    }
}

#if MANIA_USE_PLUS
void MegAmiMenu_State_EncoreStock(void)
{
    RSDK_THIS(MegAmiMenu);

    EntityPlayer *player = (EntityPlayer *)self->parent;

    int8 optionCount = 3;
    if (API.CheckDLC(DLC_PLUS))
        optionCount += 2;

    MegAmiMenu_HandleUpDown(ControllerInfo[player->controllerID], optionCount);

    if (confirmPress) {
        int8 stock = selectedOption - MEGAMIMENU_STOCK1;
        globals->stock &= ~(255 << (8 * stock));
        if (self->subSelection)
            globals->stock |= (1 << (self->subSelection - 1)) << (8 * stock);
        SetCharacterFlags();
        destroyEntity(self);
    }
    else if (backPress) {
        self->state     = MegAmiMenu_State_Main;
        self->stateDraw = StateMachine_None;
    }
}
#endif

void MegAmiMenu_State_Shield(void)
{
    RSDK_THIS(MegAmiMenu);

    EntityPlayer *player = (EntityPlayer *)self->parent;

    MegAmiMenu_HandleUpDown(ControllerInfo[player->controllerID], SHIELD_LIGHTNING);

    if (confirmPress) {
        player->shield = self->subSelection;
        Player_ApplyShield(player);
        if (player->shield == SHIELD_NONE) {
            ObjectShield *Shield = Mod.FindObject("Shield");
            Entity *powerup = RSDK_GET_ENTITY_GEN(Player->playerCount + RSDK.GetEntitySlot(player));
            if (powerup->classID == Shield->classID)
                destroyEntity(powerup);
        }
        destroyEntity(self);
    }
    else if (backPress) {
        self->state     = MegAmiMenu_State_Main;
        self->stateDraw = StateMachine_None;
    }
}

void MegAmiMenu_State_SetRings(void)
{
    RSDK_THIS(MegAmiMenu);

    EntityPlayer *player = (EntityPlayer *)self->parent;

    MegAmiMenu_HandleSetValue(ControllerInfo[player->controllerID], 0, 999);

    if (confirmPress) {
        if (self->customValue > player->rings)
            Player_GiveRings(player, self->customValue - player->rings, false);
        else
            player->rings = self->customValue;
        destroyEntity(self);
    }
    else if (backPress) {
        self->state     = MegAmiMenu_State_Main;
        self->stateDraw = StateMachine_None;
    }
}

void MegAmiMenu_State_DrawChar(void)
{
    RSDK_THIS(MegAmiMenu);

    ObjectUIWidgets *UIWidgets = Mod.FindObject("UIWidgets");

    int8 characterCount = 3;
#if MANIA_USE_PLUS
    if (API.CheckDLC(DLC_PLUS))
        characterCount += 2;
#endif

#if MANIA_USE_PLUS
    bool32 showNone = self->state == MegAmiMenu_State_P2Char || self->state == MegAmiMenu_State_EncoreStock;
#else
    bool32 showNone = self->state == MegAmiMenu_State_P2Char;
#endif

    // Set Box Width
    int32 subBoxWidth = 0;
    for (uint8 s = CHARACTER_NONE + !showNone; s <= characterCount; s++) {
        int32 stringWidth = RSDK.GetStringWidth(UIWidgets->fontFrames, 0, &MegAmiMenu->charStrings[s], 0, &MegAmiMenu->charStrings[s].length, 0);
        if (stringWidth > subBoxWidth)
            subBoxWidth = stringWidth;
    }
    subBoxWidth += 19;

    RSDK.DrawRect(SUBBOX_XPOS, BOX_YPOS, subBoxWidth, BOX_HEIGHT(characterCount + showNone), BOX_COLOR, 0xFF,
                  INK_NONE, true);

    Vector2 drawPos;

    // Draw Selection Arrow
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 8);
    drawPos.y = TO_FIXED(BOX_YPOS + 9 + (self->subSelection * OPTION_SPACING));

    self->animator.frameID = 30; // >
    RSDK.DrawSprite(&self->animator, &drawPos, true);

    // Initialize Option Text Position
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 16);
    drawPos.y = TO_FIXED(BOX_YPOS + 9);

    // Draw Option Text
    for (uint8 s = CHARACTER_NONE + !showNone; s <= characterCount; s++) {
        DrawOptionText(&MegAmiMenu->charStrings[s]);
    }
}

void MegAmiMenu_State_DrawShield(void)
{
    RSDK_THIS(MegAmiMenu);

    ObjectUIWidgets *UIWidgets = Mod.FindObject("UIWidgets");

    // Set Box Width
    int32 subBoxWidth = 0;
    for (uint8 s = SHIELD_NONE; s < SHIELD_COUNT; s++) {
        int32 stringWidth =
            RSDK.GetStringWidth(UIWidgets->fontFrames, 0, &MegAmiMenu->shieldStrings[s], 0, &MegAmiMenu->shieldStrings[s].length, 0);
        if (stringWidth > subBoxWidth)
            subBoxWidth = stringWidth;
    }
    subBoxWidth += 19;

    RSDK.DrawRect(SUBBOX_XPOS, BOX_YPOS, subBoxWidth, BOX_HEIGHT(5), BOX_COLOR, 0xFF, INK_NONE, true);

    Vector2 drawPos;

    // Draw Selection Arrow
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 8);
    drawPos.y = TO_FIXED(BOX_YPOS + 9 + (self->subSelection * OPTION_SPACING));

    self->animator.frameID = 30; // >
    RSDK.DrawSprite(&self->animator, &drawPos, true);

    // Initialize Option Text Position
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 16);
    drawPos.y = TO_FIXED(BOX_YPOS + 9);

    // Draw Option Text
    for (uint8 s = SHIELD_NONE; s < SHIELD_COUNT; s++) {
        DrawOptionText(&MegAmiMenu->shieldStrings[s]);
    }
}

void MegAmiMenu_State_DrawSetValue(void)
{
    RSDK_THIS(MegAmiMenu);

    RSDK.DrawRect(SUBBOX_XPOS, BOX_YPOS, (self->valueDigits * 8) + 10, BOX_HEIGHT(3), BOX_COLOR, 0xFF, INK_NONE, true);

    Vector2 drawPos;

    // Draw Plus Sign
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 9 + (self->subSelection * 8));
    drawPos.y = TO_FIXED(BOX_YPOS + 9);

    self->animator.frameID = 11; // +
    RSDK.DrawSprite(&self->animator, &drawPos, true);

    // Initialize Number Position
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 1 + (self->valueDigits * 8));
    drawPos.y += TO_FIXED(OPTION_SPACING);

    // Draw Number
    int32 digitCount = self->valueDigits;
    int32 digit      = 1;
    while (digitCount--) {
        int32 digitNumber      = self->customValue / digit % 10;
        self->animator.frameID = 16 + digitNumber;
        if (digitNumber == 6 || digitNumber == 7)
            drawPos.x -= TO_FIXED(1);
        RSDK.DrawSprite(&self->animator, &drawPos, true);
        digit *= 10;
        drawPos.x -= TO_FIXED(8);
        if (digitNumber == 6 || digitNumber == 7)
            drawPos.x += TO_FIXED(1);
    }

    // Draw Minus Sign
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 9 + (self->subSelection * 8));
    drawPos.y += TO_FIXED(OPTION_SPACING);

    self->animator.frameID = 13; // -
    RSDK.DrawSprite(&self->animator, &drawPos, true);
}

void MegAmiMenu_HandleTouchControls(void)
{
    RSDK_THIS(MegAmiMenu);

    EntityPlayer *player            = (EntityPlayer *)self->parent;
    RSDKControllerState *controller = &ControllerInfo[player->controllerID];

    bool32 touchedUp = false;
    if (MegAmiMenu_CheckTouchRect(0, 0, ScreenInfo->center.x, Y_THIRD)) {
        ControllerInfo->keyUp.down |= true;
        controller->keyUp.down = true;
        touchedUp              = true;
    }

    bool32 touchedDown = false;
    if (MegAmiMenu_CheckTouchRect(0, Y_THIRD * 2, ScreenInfo->center.x, ScreenInfo->size.y)) {
        ControllerInfo->keyDown.down |= true;
        controller->keyDown.down = true;
        touchedDown              = true;
    }

    bool32 touchedLeft = false;
    if (MegAmiMenu_CheckTouchRect(0, Y_THIRD, ScreenInfo->center.x / 2, Y_THIRD * 2)) {
        ControllerInfo->keyLeft.down |= true;
        controller->keyLeft.down = true;
        touchedLeft              = true;
    }

    bool32 touchedRight = false;
    if (MegAmiMenu_CheckTouchRect(ScreenInfo->center.x / 2, Y_THIRD, ScreenInfo->center.x, Y_THIRD * 2)) {
        ControllerInfo->keyRight.down |= true;
        controller->keyRight.down = true;
        touchedRight              = true;
    }

    bool32 touchedConfirm = false;
    if (MegAmiMenu_CheckTouchRect(ScreenInfo->center.x, ScreenInfo->center.y, ScreenInfo->size.x, ScreenInfo->size.y)) {
        ControllerInfo->keyStart.down |= true;
        controller->keyStart.down = true;
        touchedConfirm            = true;
    }

    bool32 touchedBack = false;
    if (MegAmiMenu_CheckTouchRect(ScreenInfo->center.x, 0, ScreenInfo->size.x, ScreenInfo->center.y)) {
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

    if (!MegAmiMenu->touchUp && touchedUp) {
        ControllerInfo->keyUp.press |= ControllerInfo->keyUp.down;
        controller->keyUp.press |= controller->keyUp.down;
    }
    MegAmiMenu->touchUp = controller->keyUp.down;

    if (!MegAmiMenu->touchDown && touchedDown) {
        ControllerInfo->keyDown.press |= ControllerInfo->keyDown.down;
        controller->keyDown.press |= controller->keyDown.down;
    }
    MegAmiMenu->touchDown = controller->keyDown.down;

    if (!MegAmiMenu->touchLeft && touchedLeft) {
        ControllerInfo->keyLeft.press |= ControllerInfo->keyLeft.down;
        controller->keyLeft.press |= controller->keyLeft.down;
    }
    MegAmiMenu->touchLeft = controller->keyLeft.down;

    if (!MegAmiMenu->touchRight && touchedRight) {
        ControllerInfo->keyRight.press |= ControllerInfo->keyRight.down;
        controller->keyRight.press |= controller->keyRight.down;
    }
    MegAmiMenu->touchRight = controller->keyRight.down;

    if (!MegAmiMenu->touchConfirm && touchedConfirm) {
        ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
        controller->keyStart.press |= controller->keyStart.down;
    }
    MegAmiMenu->touchConfirm = controller->keyStart.down;

    if (!MegAmiMenu->touchBack && touchedBack) {
        if (API_GetConfirmButtonFlip()) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        else {
            ControllerInfo->keyB.press |= ControllerInfo->keyB.down;
            controller->keyB.press |= controller->keyB.down;
        }
    }
    MegAmiMenu->touchBack = API_GetConfirmButtonFlip() ? controller->keyA.down : controller->keyB.down;
}

bool32 MegAmiMenu_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2)
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

void MegAmiMenu_HandleUpDown(RSDKControllerState controller, int8 maxCount)
{
    RSDK_THIS(MegAmiMenu);

    if (self->state == MegAmiMenu_State_Main) {
        if (controller.keyDown.press) {
            if (++self->mainSelection > maxCount)
                self->mainSelection = 0;
        }
        else if (controller.keyUp.press) {
            if (--self->mainSelection < 0)
                self->mainSelection = maxCount;
        }
    }
    else {
        if (controller.keyDown.press) {
            if (++self->subSelection > maxCount)
                self->subSelection = 0;
        }
        else if (controller.keyUp.press) {
            if (--self->subSelection < 0)
                self->subSelection = maxCount;
        }
    }
}

void MegAmiMenu_HandleSetValue(RSDKControllerState controller, int32 minValue, int32 maxValue)
{
    RSDK_THIS(MegAmiMenu);

    if (controller.keyRight.press) {
        if (++self->subSelection >= self->valueDigits)
            self->subSelection = 0;
    }
    else if (controller.keyLeft.press) {
        if (--self->subSelection < 0)
            self->subSelection = self->valueDigits - 1;
    }
    else if (controller.keyUp.press) {
        int32 digit    = self->valueDigits;
        int32 decrease = 1;
        while (--digit > self->subSelection) decrease *= 10;
        self->customValue += decrease;
        if (self->customValue > maxValue)
            self->customValue -= maxValue - minValue + 1;
    }
    else if (controller.keyDown.press) {
        int32 digit    = self->valueDigits;
        int32 decrease = 1;
        while (--digit > self->subSelection) decrease *= 10;
        self->customValue -= decrease;
        if (self->customValue < minValue)
            self->customValue += maxValue - minValue + 1;
    }
}

#if GAME_INCLUDE_EDITOR
void MegAmiMenu_EditorDraw(void)
{
    RSDK_THIS(MegAmiMenu);
    RSDK.DrawRect(self->position.x - TO_FIXED(45), self->position.y - TO_FIXED(9), TO_FIXED(90), TO_FIXED(19), BOX_COLOR, 0xFF, INK_NONE, false);
    RSDK.DrawText(&self->animator, &self->position, &self->menuStrings[0], 0, self->menuStrings[0].length, ALIGN_CENTER, 0, 0, 0, false);
}

void MegAmiMenu_EditorLoad(void) {}
#endif

void MegAmiMenu_Serialize(void) {}
