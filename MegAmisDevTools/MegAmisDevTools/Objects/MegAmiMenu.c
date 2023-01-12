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

    if (SceneInfo->state != ENGINESTATE_PAUSED)
        RSDK.SetEngineState(ENGINESTATE_PAUSED);

    EntityPlayer *player = (EntityPlayer *)self->parent;
    if (player->classID != Player->classID || ControllerInfo[player->controllerID].keySelect.press)
        destroyEntity(self);
    else {
        // Handle Touch Controls
        RSDKControllerState *controller = &ControllerInfo[player->controllerID];

        int32 yThird = ScreenInfo->size.y / 3;

        bool32 touchedUp = false;
        if (MegAmiMenu_CheckTouchRect(0, 0, ScreenInfo->center.x, yThird)) {
            ControllerInfo->keyUp.down |= true;
            controller->keyUp.down = true;
            touchedUp              = true;
        }

        bool32 touchedDown = false;
        if (MegAmiMenu_CheckTouchRect(0, yThird * 2, ScreenInfo->center.x, ScreenInfo->size.y)) {
            ControllerInfo->keyDown.down |= true;
            controller->keyDown.down = true;
            touchedDown              = true;
        }

        bool32 touchedLeft = false;
        if (MegAmiMenu_CheckTouchRect(0, yThird, ScreenInfo->center.x / 2, yThird * 2)) {
            ControllerInfo->keyLeft.down |= true;
            controller->keyLeft.down = true;
            touchedLeft              = true;
        }

        bool32 touchedRight = false;
        if (MegAmiMenu_CheckTouchRect(ScreenInfo->center.x / 2, yThird, ScreenInfo->center.x, yThird * 2)) {
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

        StateMachine_Run(self->state);
    }

    if (self->classID != MegAmiMenu->classID)
        RSDK.SetEngineState(ENGINESTATE_REGULAR);
}

void MegAmiMenu_LateUpdate(void) {}

void MegAmiMenu_StaticUpdate(void) {}

void MegAmiMenu_Draw(void)
{
    RSDK_THIS(MegAmiMenu);

    EntityPlayer *parentplayer = (EntityPlayer *)self->parent;
    EntityPlayer *camplayer    = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);

    if (RSDK.GetEntitySlot(parentplayer) == RSDK.GetEntitySlot(camplayer)) {
        RSDK.DrawRect(MAINBOX_XPOS, BOX_YPOS, MAINBOX_WIDTH, BOX_HEIGHT(MEGAMIMENU_COUNT), 0xFF0000, 0xFF, INK_NONE, true);

        Vector2 drawPos;

        // Draw Selection Arrow
        drawPos.x              = TO_FIXED(MAINBOX_XPOS + 8);
        drawPos.y              = TO_FIXED(BOX_YPOS + 9 + (self->mainSelection * OPTION_SPACING));
        self->animator.frameID = 30; // >
        RSDK.DrawSprite(&self->animator, &drawPos, true);

        // Initialize Option Text Position
        drawPos.x = TO_FIXED(MAINBOX_XPOS + 16);
        drawPos.y = TO_FIXED(BOX_YPOS + 9);

        // Draw Option Text
        RSDK.DrawText(&self->animator, &drawPos, &self->p1char, 0, self->p1char.length, ALIGN_LEFT, 0, 0, 0, true);
        drawPos.y += TO_FIXED(OPTION_SPACING);
        RSDK.DrawText(&self->animator, &drawPos, &self->p2char, 0, self->p2char.length, ALIGN_LEFT, 0, 0, 0, true);
        drawPos.y += TO_FIXED(OPTION_SPACING);
        RSDK.DrawText(&self->animator, &drawPos, &self->shield, 0, self->shield.length, ALIGN_LEFT, 0, 0, 0, true);
        drawPos.y += TO_FIXED(OPTION_SPACING);
        RSDK.DrawText(&self->animator, &drawPos, &self->shoes, 0, self->shoes.length, ALIGN_LEFT, 0, 0, 0, true);
        drawPos.y += TO_FIXED(OPTION_SPACING);
        RSDK.DrawText(&self->animator, &drawPos, &self->hyperRing, 0, self->hyperRing.length, ALIGN_LEFT, 0, 0, 0, true);
        drawPos.y += TO_FIXED(OPTION_SPACING);
        RSDK.DrawText(&self->animator, &drawPos, &self->setRings, 0, self->setRings.length, ALIGN_LEFT, 0, 0, 0, true);
        drawPos.y += TO_FIXED(OPTION_SPACING);
        RSDK.DrawText(&self->animator, &drawPos, &self->super, 0, self->super.length, ALIGN_LEFT, 0, 0, 0, true);
        drawPos.y += TO_FIXED(OPTION_SPACING);
        RSDK.DrawText(&self->animator, &drawPos, &self->inv, 0, self->inv.length, ALIGN_LEFT, 0, 0, 0, true);
        drawPos.y += TO_FIXED(OPTION_SPACING);
        RSDK.DrawText(&self->animator, &drawPos, &self->exit, 0, self->exit.length, ALIGN_LEFT, 0, 0, 0, true);

        if (self->stateDraw) {
            RSDK.DrawRect(MAINBOX_XPOS, BOX_YPOS, MAINBOX_WIDTH, BOX_HEIGHT(MEGAMIMENU_COUNT), 0x000000, 0x80, INK_ALPHA, true);
            StateMachine_Run(self->stateDraw);
        }
    }
}

void MegAmiMenu_Create(void *data)
{
    RSDK_THIS(MegAmiMenu);

    ObjectUIWidgets *uiwidgets = Mod.FindObject("UIWidgets");
    ObjectZone *zone           = Mod.FindObject("Zone");

    RSDK.SetSpriteAnimation(uiwidgets->fontFrames, 0, &self->animator, true, 0);

    if (!SceneInfo->inEditor) {
        self->active    = ACTIVE_ALWAYS;
        self->visible   = true;
        self->drawGroup = zone->hudDrawGroup;

        self->parent         = (Entity *)data;
        EntityPlayer *player = (EntityPlayer *)self->parent;

        // Initialize Strings
        RSDK.InitString(&self->p1char, "CHANGE CHARACTER", false);
        RSDK.InitString(&self->p2char, "CHANGE SIDEKICK", false);
        RSDK.InitString(&self->shield, "CHANGE SHIELD", false);
        RSDK.InitString(&self->shoes, "GIVE SPEED SHOES", false);
        RSDK.InitString(&self->hyperRing, !player->hyperRing ? "GIVE HYPER RING" : "REMOVE HYPER RING", false);
        RSDK.InitString(&self->setRings, "SET RING COUNT", false);
        RSDK.InitString(&self->super, player->superState != SUPERSTATE_SUPER ? "TURN SUPER" : "REVERT SUPER", false);
        RSDK.InitString(&self->inv, !MegAmiMenu->playerInv[player->playerID] ? "ENABLE INVINCIBILITY" : "DISABLE INVINCIBILITY", false);
        RSDK.InitString(&self->exit, "EXIT", false);
        RSDK.InitString(&self->sonic, "SONIC", false);
        RSDK.InitString(&self->tails, "TAILS", false);
        RSDK.InitString(&self->knux, "KNUCKLES", false);
#if MANIA_USE_PLUS
        RSDK.InitString(&self->mighty, "MIGHTY", false);
        RSDK.InitString(&self->ray, "RAY", false);
#endif
        RSDK.InitString(&self->none, "NONE", false);
        RSDK.InitString(&self->blue, "BLUE SHIELD", false);
        RSDK.InitString(&self->bubble, "BUBBLE SHIELD", false);
        RSDK.InitString(&self->fire, "FIRE SHIELD", false);
        RSDK.InitString(&self->lightning, "LIGHTNING SHIELD", false);

        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->p1char);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->p2char);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->shield);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->shoes);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->hyperRing);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->setRings);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->super);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->inv);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->exit);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->sonic);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->tails);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->knux);
#if MANIA_USE_PLUS
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->mighty);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->ray);
#endif
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->none);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->blue);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->bubble);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->fire);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->lightning);

        self->state     = MegAmiMenu_State_Main;
        self->stateDraw = StateMachine_None;

        MegAmiMenu->touchUp      = false;
        MegAmiMenu->touchDown    = false;
        MegAmiMenu->touchLeft    = false;
        MegAmiMenu->touchRight   = false;
        MegAmiMenu->touchConfirm = false;
        MegAmiMenu->touchBack    = false;

        RSDK.SetEngineState(ENGINESTATE_PAUSED);
    }
    else {
        RSDK.InitString(&self->p1char, "MEGAMI MENU", false);
        RSDK.SetSpriteString(uiwidgets->fontFrames, 0, &self->p1char);
    }
}

void MegAmiMenu_StageLoad(void) { MegAmiMenu->sfxFail = RSDK.GetSfx("Stage/Fail.wav"); }

void MegAmiMenu_State_Main(void)
{
    RSDK_THIS(MegAmiMenu);

    EntityPlayer *player = (EntityPlayer *)self->parent;
    bool32 confirmPress =
        ControllerInfo[player->controllerID].keyStart.press
        || (API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyB.press : ControllerInfo[player->controllerID].keyA.press);
    bool32 backPress = API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyA.press : ControllerInfo[player->controllerID].keyB.press;

    if (ControllerInfo[player->controllerID].keyDown.press) {
        if (++self->mainSelection > MEGAMIMENU_EXIT)
            self->mainSelection = MEGAMIMENU_P1CHAR;
    }
    else if (ControllerInfo[player->controllerID].keyUp.press) {
        if (--self->mainSelection < MEGAMIMENU_P1CHAR)
            self->mainSelection = MEGAMIMENU_EXIT;
    }
    else if (confirmPress) {
        switch (self->mainSelection) {
            default: break;
            case MEGAMIMENU_P1CHAR:
                self->state        = MegAmiMenu_State_P1Char;
                self->stateDraw    = MegAmiMenu_State_DrawChar;
                self->subSelection = 0;
                break;
            case MEGAMIMENU_P2CHAR:
                if (!player->sidekick || !globals->gameMode == MODE_COMPETITION) {
                    self->state        = MegAmiMenu_State_P2Char;
                    self->stateDraw    = MegAmiMenu_State_DrawChar;
                    self->subSelection = 0;
                }
                else
                    RSDK.PlaySfx(MegAmiMenu->sfxFail, false, 255);
                break;
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
            case MEGAMIMENU_HYPERRING:
                player->hyperRing ^= true;
                destroyEntity(self);
                break;
            case MEGAMIMENU_SETRINGS:
                self->state        = MegAmiMenu_State_SetRings;
                self->stateDraw    = MegAmiMenu_State_DrawSetValue;
                self->subSelection = 0;
                self->customValue  = player->rings;
                self->valueDigits  = 3;
                break;
            case MEGAMIMENU_SUPER:
                if (player->superState != SUPERSTATE_SUPER) {
                    Player_GiveRings(player, 50, false);
                    Player_TryTransform(player, 0x7F);
                }
                else
                    player->superState = SUPERSTATE_FADEOUT;
                destroyEntity(self);
                break;
            case MEGAMIMENU_INV:
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
    bool32 confirmPress =
        ControllerInfo[player->controllerID].keyStart.press
        || (API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyB.press : ControllerInfo[player->controllerID].keyA.press);
    bool32 backPress = API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyA.press : ControllerInfo[player->controllerID].keyB.press;

    if (ControllerInfo[player->controllerID].keyDown.press) {
#if MANIA_USE_PLUS
        if (++self->subSelection > (API.CheckDLC(DLC_PLUS) ? 4 : 2))
#else
        if (++self->subSelection > 2)
#endif
            self->subSelection = 0;
    }
    else if (ControllerInfo[player->controllerID].keyUp.press) {
        if (--self->subSelection < 0)
#if MANIA_USE_PLUS
            self->subSelection = (API.CheckDLC(DLC_PLUS) ? 4 : 2);
#else
            self->subSelection = 2;
#endif
    }
    else if (confirmPress) {
        Player_ChangeCharacter(player, 1 << self->subSelection);
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
    bool32 confirmPress =
        ControllerInfo[player->controllerID].keyStart.press
        || (API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyB.press : ControllerInfo[player->controllerID].keyA.press);
    bool32 backPress = API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyA.press : ControllerInfo[player->controllerID].keyB.press;

    if (ControllerInfo[player->controllerID].keyDown.press) {
#if MANIA_USE_PLUS
        if (++self->subSelection > (API.CheckDLC(DLC_PLUS) ? 5 : 3))
#else
        if (++self->subSelection > 3)
#endif
            self->subSelection = 0;
    }
    else if (ControllerInfo[player->controllerID].keyUp.press) {
        if (--self->subSelection < 0)
#if MANIA_USE_PLUS
            self->subSelection = (API.CheckDLC(DLC_PLUS) ? 5 : 3);
#else
            self->subSelection = 3;
#endif
    }
    else if (confirmPress) {
        EntityPlayer *sidekick = RSDK_GET_ENTITY(RSDK.GetEntitySlot(player) + 1, Player);
        if (sidekick->classID == Player->classID) {
            // P2 already exists, just change the character
            if (self->subSelection == 0) {
                Player_ChangeCharacter(sidekick, ID_NONE);
                destroyEntity(sidekick);

                // Handle new player count
                ObjectShield *Shield         = Mod.FindObject("Shield");
                EntityShield *shield         = RSDK_GET_ENTITY(RSDK.GetEntitySlot(player) + Player->playerCount, Shield);
                ObjectImageTrail *ImageTrail = Mod.FindObject("ImageTrail");
                EntityImageTrail *powerup    = RSDK_GET_ENTITY(2 * Player->playerCount + RSDK.GetEntitySlot(player), ImageTrail);
#if MANIA_USE_PLUS
                Player->playerCount = globals->gameMode == MODE_ENCORE ? 2 : RSDK.GetEntityCount(Player->classID, false);
#else
                Player->playerCount = RSDK.GetEntityCount(Player->classID, false);
#endif
                if (shield->classID)
                    RSDK.CopyEntity(RSDK_GET_ENTITY_GEN(RSDK.GetEntitySlot(player) + Player->playerCount), shield, true);
                if (powerup->classID)
                    RSDK.CopyEntity(RSDK_GET_ENTITY_GEN(2 * Player->playerCount + RSDK.GetEntitySlot(player)), powerup, true);
            }
            else
                Player_ChangeCharacter(sidekick, 1 << (self->subSelection - 1));
        }
        else if (self->subSelection > 0) {
            // P2 doesn't exist, spawn them
            ObjectImageTrail *ImageTrail = Mod.FindObject("ImageTrail");
            EntityImageTrail *powerup    = RSDK_GET_ENTITY(2 * Player->playerCount + RSDK.GetEntitySlot(player), ImageTrail);
            if (powerup->classID)
                RSDK.CopyEntity(RSDK_GET_ENTITY_GEN(RSDK.GetEntitySlot(powerup) + 2), powerup, true);

            if (sidekick->classID) // If this is a powerup
                RSDK.CopyEntity(RSDK_GET_ENTITY_GEN(RSDK.GetEntitySlot(sidekick) + 1), sidekick, false);
            destroyEntity(sidekick);

            sidekick->classID   = Player->classID;
            Player->jumpInTimer = 0;
            sidekick->playerID  = 1;

            ObjectDust *Dust  = Mod.FindObject("Dust");
            EntityDust *dust  = CREATE_ENTITY(Dust, INT_TO_VOID(1), sidekick->position.x, sidekick->position.y);
            dust->visible     = false;
            dust->active      = ACTIVE_NEVER;
            dust->isPermanent = true;
            dust->position.y  = TO_FIXED(ScreenInfo->position.y - 128);

            ObjectZone *Zone = Mod.FindObject("Zone");
            Player_ChangeCharacter(sidekick, 1 << (self->subSelection - 1));
            sidekick->velocity.x = 0;
            sidekick->velocity.y = 0;
            sidekick->groundVel  = 0;
            sidekick->position.x = -TO_FIXED(64);
            sidekick->position.y = -TO_FIXED(64);
            sidekick->camera     = NULL;
            sidekick->angle      = 0x80;
            if (sidekick->characterID == ID_TAILS)
                sidekick->state = Player_State_FlyToPlayer;
            else {
                sidekick->state            = Player_State_ReturnToPlayer;
                sidekick->abilityValues[0] = ((ScreenInfo->position.y + ScreenInfo->size.y + 16) << 16) - player->position.y;
                sidekick->drawFX |= FX_SCALE;
                sidekick->scale.x    = 0x400;
                sidekick->scale.y    = 0x400;
                sidekick->velocity.y = CLAMP(sidekick->abilityValues[0] / -12, -0xE0000, -0x68000);
            }
            sidekick->abilityPtrs[0]   = dust;
            sidekick->abilityValues[0] = 0;
            sidekick->nextAirState     = StateMachine_None;
            sidekick->nextGroundState  = StateMachine_None;
            sidekick->stateInput       = Player_Input_P2_Delay;
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
        destroyEntity(self);
    }
    else if (backPress) {
        self->state     = MegAmiMenu_State_Main;
        self->stateDraw = StateMachine_None;
    }
}

void MegAmiMenu_State_Shield(void)
{
    RSDK_THIS(MegAmiMenu);

    EntityPlayer *player = (EntityPlayer *)self->parent;
    bool32 confirmPress =
        ControllerInfo[player->controllerID].keyStart.press
        || (API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyB.press : ControllerInfo[player->controllerID].keyA.press);
    bool32 backPress = API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyA.press : ControllerInfo[player->controllerID].keyB.press;

    if (ControllerInfo[player->controllerID].keyDown.press) {
        if (++self->subSelection > SHIELD_LIGHTNING)
            self->subSelection = SHIELD_NONE;
    }
    else if (ControllerInfo[player->controllerID].keyUp.press) {
        if (--self->subSelection < SHIELD_NONE)
            self->subSelection = SHIELD_LIGHTNING;
    }
    else if (confirmPress) {
        player->shield = self->subSelection;
        Player_ApplyShield(player);
        if (player->shield == SHIELD_NONE) {
            ObjectShield *Shield = Mod.FindObject("Shield");
            destroyEntity(RSDK_GET_ENTITY(Player->playerCount + RSDK.GetEntitySlot(player), Shield));
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
    bool32 confirmPress =
        ControllerInfo[player->controllerID].keyStart.press
        || (API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyB.press : ControllerInfo[player->controllerID].keyA.press);
    bool32 backPress = API_GetConfirmButtonFlip() ? ControllerInfo[player->controllerID].keyA.press : ControllerInfo[player->controllerID].keyB.press;

    if (ControllerInfo[player->controllerID].keyRight.press) {
        if (++self->subSelection > 2)
            self->subSelection = 0;
    }
    else if (ControllerInfo[player->controllerID].keyLeft.press) {
        if (--self->subSelection < 0)
            self->subSelection = 2;
    }
    else if (ControllerInfo[player->controllerID].keyDown.press) {
        switch (self->subSelection) {
            case 0: self->customValue -= 100; break;
            case 1: self->customValue -= 10; break;
            case 2: self->customValue--; break;
        }
        if (self->customValue < 0)
            self->customValue += 1000;
    }
    else if (ControllerInfo[player->controllerID].keyUp.press) {
        switch (self->subSelection) {
            case 0: self->customValue += 100; break;
            case 1: self->customValue += 10; break;
            case 2: self->customValue++; break;
        }
        if (self->customValue > 999)
            self->customValue -= 1000;
    }
    else if (confirmPress) {
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

#if MANIA_USE_PLUS
    uint8 optionCount = (API.CheckDLC(DLC_PLUS) ? 5 : 3) + (self->mainSelection == MEGAMIMENU_P2CHAR);
#else
    uint8 optionCount = 3 + (self->mainSelection == MEGAMIMENU_P2CHAR);
#endif

    RSDK.DrawRect(SUBBOX_XPOS, BOX_YPOS, 80, BOX_HEIGHT(optionCount), 0xFF0000, 0xFF, INK_NONE, true);

    Vector2 drawPos;

    // Draw Selection Arrow
    drawPos.x              = TO_FIXED(SUBBOX_XPOS + 8);
    drawPos.y              = TO_FIXED(BOX_YPOS + 9 + (self->subSelection * OPTION_SPACING));
    self->animator.frameID = 30; // >
    RSDK.DrawSprite(&self->animator, &drawPos, true);

    // Initialize Option Text Position
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 16);
    drawPos.y = TO_FIXED(BOX_YPOS + 9);

    // Draw Option Text
    if (self->mainSelection == MEGAMIMENU_P2CHAR) {
        RSDK.DrawText(&self->animator, &drawPos, &self->none, 0, self->none.length, ALIGN_LEFT, 0, 0, 0, true);
        drawPos.y += TO_FIXED(OPTION_SPACING);
    }
    RSDK.DrawText(&self->animator, &drawPos, &self->sonic, 0, self->sonic.length, ALIGN_LEFT, 0, 0, 0, true);
    drawPos.y += TO_FIXED(OPTION_SPACING);
    RSDK.DrawText(&self->animator, &drawPos, &self->tails, 0, self->tails.length, ALIGN_LEFT, 0, 0, 0, true);
    drawPos.y += TO_FIXED(OPTION_SPACING);
    RSDK.DrawText(&self->animator, &drawPos, &self->knux, 0, self->knux.length, ALIGN_LEFT, 0, 0, 0, true);
#if MANIA_USE_PLUS
    if (API.CheckDLC(DLC_PLUS)) {
        drawPos.y += TO_FIXED(OPTION_SPACING);
        RSDK.DrawText(&self->animator, &drawPos, &self->mighty, 0, self->mighty.length, ALIGN_LEFT, 0, 0, 0, true);
        drawPos.y += TO_FIXED(OPTION_SPACING);
        RSDK.DrawText(&self->animator, &drawPos, &self->ray, 0, self->ray.length, ALIGN_LEFT, 0, 0, 0, true);
    }
#endif
}

void MegAmiMenu_State_DrawShield(void)
{
    RSDK_THIS(MegAmiMenu);

    RSDK.DrawRect(SUBBOX_XPOS, BOX_YPOS, 130, BOX_HEIGHT(5), 0xFF0000, 0xFF, INK_NONE, true);

    Vector2 drawPos;

    // Draw Selection Arrow
    drawPos.x              = TO_FIXED(SUBBOX_XPOS + 8);
    drawPos.y              = TO_FIXED(BOX_YPOS + 9 + (self->subSelection * OPTION_SPACING));
    self->animator.frameID = 30; // >
    RSDK.DrawSprite(&self->animator, &drawPos, true);

    // Initialize Option Text Position
    drawPos.x = TO_FIXED(SUBBOX_XPOS + 16);
    drawPos.y = TO_FIXED(BOX_YPOS + 9);

    // Draw Option Text
    RSDK.DrawText(&self->animator, &drawPos, &self->none, 0, self->none.length, ALIGN_LEFT, 0, 0, 0, true);
    drawPos.y += TO_FIXED(OPTION_SPACING);
    RSDK.DrawText(&self->animator, &drawPos, &self->blue, 0, self->blue.length, ALIGN_LEFT, 0, 0, 0, true);
    drawPos.y += TO_FIXED(OPTION_SPACING);
    RSDK.DrawText(&self->animator, &drawPos, &self->bubble, 0, self->bubble.length, ALIGN_LEFT, 0, 0, 0, true);
    drawPos.y += TO_FIXED(OPTION_SPACING);
    RSDK.DrawText(&self->animator, &drawPos, &self->fire, 0, self->fire.length, ALIGN_LEFT, 0, 0, 0, true);
    drawPos.y += TO_FIXED(OPTION_SPACING);
    RSDK.DrawText(&self->animator, &drawPos, &self->lightning, 0, self->lightning.length, ALIGN_LEFT, 0, 0, 0, true);
}

void MegAmiMenu_State_DrawSetValue(void)
{
    RSDK_THIS(MegAmiMenu);

    RSDK.DrawRect(SUBBOX_XPOS, BOX_YPOS, (self->valueDigits * 8) + 11, BOX_HEIGHT(3), 0xFF0000, 0xFF, INK_NONE, true);

    Vector2 drawPos;

    // Draw Plus Sign
    drawPos.x              = TO_FIXED(SUBBOX_XPOS + 9 + (self->subSelection * 8));
    drawPos.y              = TO_FIXED(BOX_YPOS + 9);
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

#if RETRO_INCLUDE_EDITOR
void MegAmiMenu_EditorDraw(void)
{
    RSDK_THIS(MegAmiMenu);

    RSDK.DrawRect(self->position.x - TO_FIXED(45), self->position.y - TO_FIXED(9), TO_FIXED(90), TO_FIXED(19), 0xFF0000, 0xFF, INK_NONE, false);

    RSDK.DrawText(&self->animator, &self->position, &self->p1char, 0, self->p1char.length, ALIGN_CENTER, 0, 0, 0, false);
}

void MegAmiMenu_EditorLoad(void) {}
#endif

void MegAmiMenu_Serialize(void) {}
