#include "GameAPI/Game.h"
#include "ItemBox.h"
#include "Player.h"
#include "Misc.h"

ObjectItemBox *ItemBox;
ModObjectItemBox *Mod_ItemBox;

void ItemBox_StaticUpdate(void)
{
    RSDK_THIS(ItemBox);

    Mod.Super(ItemBox->classID, SUPER_STATICUPDATE, NULL);

    // Fade Colors
    Mod_ItemBox->boxColorTimer += 6;
    if (Mod_ItemBox->boxColorTimer >= 0x100) {
        Mod_ItemBox->boxColorTimer -= 0x100;
        RSDK.RotatePalette(1, 87, 90, false);
        RSDK.RotatePalette(2, 87, 90, false);
    }
    RSDK.SetLimitedFade(0, 1, 2, Mod_ItemBox->boxColorTimer, 87, 90);

    // Rotate
    Mod_ItemBox->angleZ = (Mod_ItemBox->angleZ + 4) & 0x3FF;
    Mod_ItemBox->angleY = (Mod_ItemBox->angleY + 4) & 0x3FF;

    Mod_ItemBox->yOffset = BadnikHelpers_Oscillate(0, 2, 10);
}

void ItemBox_Draw(void)
{
    RSDK_THIS(ItemBox);

    ObjectZone *Zone = Mod.FindObject("Zone");

    if (!self->hidden) {
        if (self->isContents) {
            if (SceneInfo->currentDrawGroup == Zone->playerDrawGroup[1]) {
                self->drawFX = FX_NONE;
                RSDK.DrawSprite(&self->contentsAnimator, &self->contentsPos, false);
            }
            else {
                RSDK.AddDrawListRef(Zone->playerDrawGroup[1], SceneInfo->entitySlot);
            }
        }
        else {
            self->inkEffect = INK_NONE;
            RSDK.DrawSprite(&self->contentsAnimator, &self->contentsPos, false);

            RSDK.Prepare3DScene(Mod_ItemBox->sceneIndex);
            RSDK.AddModelTo3DScene(Mod_ItemBox->modelIndex, Mod_ItemBox->sceneIndex, S3D_WIREFRAME_SHADED, &self->matWorld, &self->matNormal,
                                   RSDK.GetPaletteEntry(0, 87));
            RSDK.Draw3DScene(Mod_ItemBox->sceneIndex);
        }
    }
}

void ItemBox_StageLoad(void)
{
    Mod.Super(ItemBox->classID, SUPER_STAGELOAD, NULL);
    ItemBox->sfxDestroy = RSDK.GetSfx("Global/ItemBox.wav");

    Mod_ItemBox->modelIndex = RSDK.LoadMesh("Global/ItemBox.bin", SCOPE_STAGE);
    Mod_ItemBox->sceneIndex = RSDK.Create3DScene("View:ItemBox", 512, SCOPE_STAGE);

    // sets diffuse colour (overrides)
    RSDK.SetDiffuseColor(Mod_ItemBox->sceneIndex, 0xA0, 0xA0, 0xA0);
    // sets diffuse intensity (0-8 means more diffuse, any more and it'll start darkening to black (9-12), any greater than 11 is full black)
    RSDK.SetDiffuseIntensity(Mod_ItemBox->sceneIndex, 8, 8, 8);
    // sets specular (highlight) intensity (16-0, 16 = none, 0 = all)
    RSDK.SetSpecularIntensity(Mod_ItemBox->sceneIndex, 14, 14, 14);

    // Setup Colors
    RSDK.SetPaletteEntry(0, 87, 0x0808F8);
    RSDK.SetPaletteEntry(0, 88, 0x00F818);
    RSDK.SetPaletteEntry(0, 89, 0xF8F800);
    RSDK.SetPaletteEntry(0, 90, 0xF000F0);
    RSDK.CopyPalette(0, 87, 1, 87, 4);
    RSDK.CopyPalette(0, 87, 2, 87, 4);
    RSDK.RotatePalette(2, 87, 90, false);
}

void ItemBox_CheckHit_New(void)
{
    RSDK_THIS(ItemBox);

    ObjectPlayer *Player = Mod.FindObject("Player");

    foreach_active(Player, player)
    {
        if (self->planeFilter <= 0 || player->collisionPlane == (((uint8)self->planeFilter - 1) & 1)) {
            if (Player_CheckCollisionTouch(player, self, &ItemBox->hitboxItemBox) && !player->sidekick) {
                ItemBox_Break_New(self, player);
                foreach_break;
            }
        }
    }
}

void ItemBox_Break_New(EntityItemBox *itemBox, EntityPlayer *player)
{
    if (globals->gameMode == MODE_COMPETITION) {
        EntityCompetitionSession *session = (EntityCompetitionSession *)globals->competitionSession;
        ++session->items[RSDK.GetEntitySlot(player)];
    }

    RSDK.CreateEntity(TYPE_DEFAULTOBJECT, NULL, itemBox->position.x, itemBox->position.y);

    itemBox->storedEntity  = (Entity *)player;
    itemBox->alpha         = 0x100;
    itemBox->contentsSpeed = -TO_FIXED(3);
    itemBox->active        = ACTIVE_NORMAL;
    itemBox->velocity.y    = -TO_FIXED(2);
    itemBox->isContents    = true;
    itemBox->state         = ItemBox_State_Break;
    RSDK.SetSpriteAnimation(ItemBox->aniFrames, 1, &itemBox->boxAnimator, true, 0);
    itemBox->boxAnimator.frameID = ItemBox->brokenFrame++;
    ItemBox->brokenFrame %= 3;
    RSDK.SetSpriteAnimation(-1, 0, &itemBox->overlayAnimator, true, 0);
    RSDK.SetSpriteAnimation(-1, 0, &itemBox->debrisAnimator, true, 0);

    ObjectDebris *Debris = Mod.FindObject("Debris");
    ObjectZone *Zone     = Mod.FindObject("Zone");

    for (int32 d = 0; d < 12; ++d) {
        EntityDebris *debris    = CREATE_ENTITY(Debris, NULL, itemBox->position.x + RSDK.Rand(-0x80000, 0x80000),
                                                itemBox->position.y + RSDK.Rand(-TO_FIXED(8), TO_FIXED(8)));
        debris->state           = Debris_State_Fall;
        debris->gravityStrength = 0x4000;
        debris->velocity.x      = RSDK.Rand(0, TO_FIXED(2));
        if (debris->position.x < itemBox->position.x)
            debris->velocity.x = -debris->velocity.x;
        debris->velocity.y = RSDK.Rand(-TO_FIXED(4), -TO_FIXED(1));
        debris->drawFX     = FX_FLIP;
        debris->direction  = d & 3;
        debris->drawGroup  = Zone->objectDrawGroup[1];
        RSDK.SetSpriteAnimation(ItemBox->aniFrames, 6, &debris->animator, true, RSDK.Rand(0, 4));
    }

    RSDK.PlaySfx(ItemBox->sfxDestroy, false, 255);

    itemBox->active = ACTIVE_NORMAL;
    if (itemBox->type == ITEMBOX_RANDOM) {
#if MANIA_USE_PLUS
        if (globals->gameMode != MODE_ENCORE) {
#endif
            while (true) {
                itemBox->type = RSDK.Rand(0, 13);
                switch (itemBox->type) {
                    case ITEMBOX_1UP_SONIC:
                        if (globals->gameMode == MODE_TIMEATTACK)
                            continue;

                        switch (player->characterID) {
                            case ID_SONIC: itemBox->type = ITEMBOX_1UP_SONIC; break;
                            case ID_TAILS: itemBox->type = ITEMBOX_1UP_TAILS; break;
                            case ID_KNUCKLES: itemBox->type = ITEMBOX_1UP_KNUX; break;
#if MANIA_USE_PLUS
                            case ID_MIGHTY: itemBox->type = ITEMBOX_1UP_MIGHTY; break;
                            case ID_RAY: itemBox->type = ITEMBOX_1UP_RAY;
#endif
                                break;
                            default: break;
                        }
                        itemBox->contentsAnimator.frameID = itemBox->type;
                        break;

                    case ITEMBOX_1UP_TAILS:
                    case ITEMBOX_1UP_KNUX:
#if MANIA_USE_PLUS
                    case ITEMBOX_1UP_MIGHTY:
                    case ITEMBOX_1UP_RAY:
#endif
                        continue;

                    case ITEMBOX_SWAP:
                        if (globals->gameMode != MODE_COMPETITION)
                            continue;
                        itemBox->contentsAnimator.frameID = itemBox->type;
                        break;

                    default: itemBox->contentsAnimator.frameID = itemBox->type; break;
                }
                break;
            }
#if MANIA_USE_PLUS
        }
#endif
    }
}

void ItemBox_HandleBox(void)
{
    RSDK_THIS(ItemBox);

    // Position Contents
    self->contentsPos.x = self->position.x;
    self->contentsPos.y = self->position.y + Mod_ItemBox->yOffset;

    // Handle Model
    RSDK.MatrixScaleXYZ(&self->matTransform, 0x180, 0x180, 0x180);
    RSDK.MatrixTranslateXYZ(&self->matTransform, self->position.x, self->position.y + Mod_ItemBox->yOffset, 0, false);
    RSDK.MatrixRotateXYZ(&self->matWorld, 0, Mod_ItemBox->angleY, Mod_ItemBox->angleZ);
    RSDK.MatrixMultiply(&self->matWorld, &self->matWorld, &self->matTransform);
    RSDK.MatrixRotateX(&self->matTempRot, 0x1E0);
    RSDK.MatrixRotateXYZ(&self->matNormal, 0, Mod_ItemBox->angleY, Mod_ItemBox->angleZ);
    RSDK.MatrixMultiply(&self->matNormal, &self->matNormal, &self->matTempRot);
}

bool32 ItemBox_State_IconFinish_Hook(bool32 skipped)
{
    RSDK_THIS(ItemBox);

    ObjectLRZConvItem *LRZConvItem = Mod.FindObject("LRZConvItem");

    if (LRZConvItem && self->lrzConvPhys)
        LRZConvItem_HandleLRZConvPhys(self);
    else
        ItemBox_HandleFallingCollision();

    RSDK.ProcessAnimation(&self->contentsAnimator);

    if (self->contentsAnimator.frameID == self->contentsAnimator.frameCount - 1) {
        destroyEntity(self);
    }

    return true;
}

bool32 ItemBox_State_Idle_Hook(bool32 skipped)
{
    RSDK_THIS(ItemBox);

    ItemBox_HandleBox();
    ItemBox_HandleObjectCollisions();
    ItemBox_CheckHit_New();

    RSDK.ProcessAnimation(&self->overlayAnimator);

#if MANIA_USE_PLUS
    if (self->type == ITEMBOX_STOCK) {
        RSDK.ProcessAnimation(&self->contentsAnimator);

        if (!API.CheckDLC(DLC_PLUS) && self->contentsAnimator.frameID >= 3)
            self->contentsAnimator.frameID = 0;
    }
#endif

    if (self->timer) {
        self->timer--;
    }
    else {
        RSDK.ProcessAnimation(&self->debrisAnimator);

        if (!self->debrisAnimator.frameID) {
            self->timer                        = RSDK.Rand(1, 15);
            self->debrisAnimator.frameDuration = RSDK.Rand(1, 32);
        }
    }

    return true;
}

bool32 ItemBox_State_Falling_Hook(bool32 skipped)
{
    RSDK_THIS(ItemBox);

    if (ItemBox_HandleFallingCollision())
        self->state = ItemBox_State_Idle;

    ItemBox_HandleBox();
    ItemBox_CheckHit_New();
    RSDK.ProcessAnimation(&self->overlayAnimator);

#if MANIA_USE_PLUS
    if (self->type == ITEMBOX_STOCK) {
        RSDK.ProcessAnimation(&self->contentsAnimator);

        if (!API.CheckDLC(DLC_PLUS) && self->contentsAnimator.frameID >= 3)
            self->contentsAnimator.frameID = 0;
    }
#endif

    if (self->timer) {
        self->timer--;
    }
    else {
        RSDK.ProcessAnimation(&self->debrisAnimator);

        if (!self->debrisAnimator.frameID) {
            self->timer                        = RSDK.Rand(1, 15);
            self->debrisAnimator.frameDuration = RSDK.Rand(1, 32);
        }
    }

    return true;
}

bool32 ItemBox_State_Conveyor_Hook(bool32 skipped)
{
    RSDK_THIS(ItemBox);

    self->moveOffset = LRZConvItem_HandleLRZConvPhys(self);

    ItemBox_HandleBox();
    ItemBox_CheckHit_New();

    RSDK.ProcessAnimation(&self->overlayAnimator);

#if MANIA_USE_PLUS
    if (self->type == ITEMBOX_STOCK) {
        RSDK.ProcessAnimation(&self->contentsAnimator);

        if (!API.CheckDLC(DLC_PLUS) && self->contentsAnimator.frameID >= 3)
            self->contentsAnimator.frameID = 0;
    }
#endif

    if (self->timer) {
        self->timer--;
    }
    else {
        RSDK.ProcessAnimation(&self->debrisAnimator);

        if (!self->debrisAnimator.frameID) {
            self->timer                        = RSDK.Rand(1, 15);
            self->debrisAnimator.frameDuration = RSDK.Rand(1, 32);
        }
    }

    return true;
}