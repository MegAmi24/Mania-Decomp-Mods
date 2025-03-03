#include "GameAPI/Game.h"
#include "HUD.h"

ObjectHUD *HUD;
ModObjectHUD *Mod_HUD;

void HUD_Update(void)
{
    RSDK_THIS(HUD);

    if (self->state != HUD_State_MoveOut && self->scorePos.x == (self->targetPos - TO_FIXED(0x100)))
        self->healthPos.x = self->targetPos - TO_FIXED(0x130);

    Mod.Super(HUD->classID, SUPER_UPDATE, NULL);
}

void HUD_Draw(void)
{
    RSDK_THIS(HUD);
    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);

    Vector2 drawPos, ringPos, healthPos;

    ringPos.x = self->ringsPos.x;
    ringPos.y = self->ringsPos.y;

    healthPos.x = self->healthPos.x;
    healthPos.y = self->healthPos.y;

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_COMPETITION) {
        ringPos.x = self->vsRingsPos[SceneInfo->currentScreenID].x;
        ringPos.y = self->vsRingsPos[SceneInfo->currentScreenID].y;

        healthPos.x = self->vsHealthPos[SceneInfo->currentScreenID].x;
        healthPos.y = self->vsHealthPos[SceneInfo->currentScreenID].y;
    }
#endif

    ObjectZone *Zone = Mod.FindObject("Zone");

    // Draw "Health"
    self->healthTextAnimator.frameID = player->health > 1 ? 0 : ((Zone->persistentTimer >> 3) & 1);
    RSDK.DrawSprite(&self->healthTextAnimator, &healthPos, true);

    // Draw Health
    drawPos.x = healthPos.x + TO_FIXED(93);
#if MANIA_USE_PLUS
    self->healthIconAnimator.frameID = HUD_CharacterIndexFromID(player->characterID);
#else
    switch (player->characterID) {
        case ID_SONIC:
        case ID_TAILS: self->healthIconAnimator.frameID = (player->characterID - 1); break;
        case ID_KNUCKLES: self->healthIconAnimator.frameID = 2; break;
    }
#endif
    for (int32 i = player->health; i > 0; --i) {
        drawPos.y = healthPos.y;
        if (i > 5)
            drawPos.y += TO_FIXED(16);
        RSDK.DrawSprite(&self->healthIconAnimator, &drawPos, true);
        drawPos.x -= TO_FIXED(8);
        if (i == 6)
            drawPos.x = healthPos.x + TO_FIXED(93);
    }

    player->hyperRing = false;

    Mod.Super(HUD->classID, SUPER_DRAW, NULL);

    // Draw non-flashing "Rings"
    self->hudElementsAnimator.frameID = 3;
    RSDK.DrawSprite(&self->hudElementsAnimator, &ringPos, true);
}

void HUD_Create(void *data)
{
    RSDK_THIS(HUD);

    if (!SceneInfo->inEditor) {
        self->healthPos.x = TO_FIXED(16);
        self->healthPos.y = TO_FIXED(60);

#if MANIA_USE_PLUS
        for (int32 i = 0; i < SCREEN_COUNT; ++i) {
            self->vsHealthPos[i].x = self->healthPos.x;
            self->vsHealthPos[i].y = self->healthPos.y;
        }
#endif

        RSDK.SetSpriteAnimation(Mod_HUD->healthFrames, 0, &self->healthTextAnimator, true, 0);
        RSDK.SetSpriteAnimation(Mod_HUD->healthFrames, 1, &self->healthIconAnimator, true, 0);
    }

    Mod.Super(HUD->classID, SUPER_CREATE, data);
}

void HUD_StageLoad(void)
{
    RSDK_THIS(HUD);

    Mod.Super(HUD->classID, SUPER_STAGELOAD, NULL);

    Mod_HUD->healthFrames = RSDK.LoadSpriteAnimation("Global/HealthMeter.bin", SCOPE_STAGE);
}

void HUD_State_MoveIn_Hook(void)
{
    RSDK_THIS(HUD);

#if MANIA_USE_PLUS
    Vector2 *healthPos = NULL;
    int32 *targetPos   = NULL;

    if (globals->gameMode == MODE_COMPETITION) {
        healthPos = &self->vsHealthPos[SceneInfo->currentScreenID];
        targetPos = &self->vsTargetPos[SceneInfo->currentScreenID];
    }
    else {
        healthPos = &self->healthPos;
        targetPos = &self->targetPos;
    }

    if (healthPos->x < *targetPos)
        healthPos->x += TO_FIXED(8);
#else
    if (self->healthPos.x < self->targetPos)
        self->healthPos.x += TO_FIXED(8);
#endif
}

void HUD_State_MoveOut_Hook(void)
{
    RSDK_THIS(HUD);

#if MANIA_USE_PLUS
    Vector2 *ringsPos = NULL, *healthPos = NULL, *lifePos = NULL;

    if (globals->gameMode == MODE_COMPETITION) {
        ringsPos  = &self->vsRingsPos[self->screenID];
        healthPos = &self->vsHealthPos[self->screenID];
        lifePos   = &self->vsLifePos[self->screenID];
    }
    else {
        ringsPos  = &self->ringsPos;
        healthPos = &self->healthPos;
        lifePos   = &self->lifePos;
    }

    if (healthPos->x - ringsPos->x > TO_FIXED(16)) {
        healthPos->x -= TO_FIXED(8);
        lifePos->x += TO_FIXED(8);
    }

    if (lifePos->x - healthPos->x > TO_FIXED(16))
        lifePos->x -= TO_FIXED(8);
#else
    if (self->healthPos.x - self->ringsPos.x > TO_FIXED(16)) {
        self->healthPos.x -= TO_FIXED(8);
        self->lifePos.x += TO_FIXED(8);
    }

    if (self->lifePos.x - self->healthPos.x > TO_FIXED(16))
        self->lifePos.x -= TO_FIXED(8);
#endif
}