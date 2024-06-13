#include "GameAPI/Game.h"
#include "Player.h"
#include "ModConfig.h"

ObjectPlayer *Player;
ModObjectPlayer *Mod_Player;

void Player_SetOuttaHere(void)
{
    RSDK_THIS(Player);

    // Wait for ~3 minutes to do outta here
    if (self->outtaHereTimer >= 10620) {
        // Check for character related things
        bool32 canOuttaHere = false;
        uint16 outtaHereSfx = Player->sfxOuttahere;
        int16 outtaHereAnim = ANI_OUTTA_HERE;
        switch (self->characterID) {
            case ID_SONIC:
                if (config.sonicCanOuttaHere)
                    canOuttaHere = true;
                if (self->superState != SUPERSTATE_SUPER)
                    outtaHereAnim = config.sonicAnimID;
                else
                    outtaHereAnim = config.superSonicAnimID;
                break;

            case ID_TAILS:
                if (config.tailsCanOuttaHere)
                    canOuttaHere = true;
                outtaHereAnim = config.tailsAnimID;
                if (config.useVoiceLines == 2)
                    outtaHereSfx = Mod_Player->sfxOuttahereT;
                break;

            case ID_KNUCKLES:
                if (config.knuxCanOuttaHere)
                    canOuttaHere = true;
                outtaHereAnim = config.knuxAnimID;
                if (config.useVoiceLines == 2)
                    outtaHereSfx = Mod_Player->sfxOuttahereK;
                break;

#if MANIA_USE_PLUS
            case ID_MIGHTY:
                if (config.mightyCanOuttaHere)
                    canOuttaHere = true;
                outtaHereAnim = config.mightyAnimID;
                if (config.useVoiceLines == 2)
                    outtaHereSfx = Mod_Player->sfxOuttahereM;
                break;

            case ID_RAY:
                if (config.rayCanOuttaHere)
                    canOuttaHere = true;
                outtaHereAnim = config.rayAnimID;
                if (config.useVoiceLines == 2)
                    outtaHereSfx = Mod_Player->sfxOuttahereR;
                break;
#endif
        }

        if (canOuttaHere && self->sidekick) {
            canOuttaHere = config.sidekickCanOuttaHere > 0;
            if (config.sidekickCanOuttaHere == 2)
                outtaHereAnim = config.sidekickAnimID;
        }

        if (!canOuttaHere)
            return;

        if (outtaHereAnim < 0)
            RSDK.SetSpriteAnimation(
                RSDK.LoadSpriteAnimation("Players/OuttaHere.bin", SCOPE_STAGE),
                (self->characterID == ID_SONIC && self->superState == SUPERSTATE_SUPER) ? 0 : (HUD_CharacterIndexFromID(self->characterID) + 1),
                &self->animator, false, 0);
        else
            RSDK.SetSpriteAnimation(self->aniFrames, outtaHereAnim, &self->animator, false, 0);
        self->state           = Mod.GetPublicFunction(NULL, "Player_State_OuttaHere");
        self->tileCollisions  = TILECOLLISION_NONE;
        self->interaction     = false;
        self->nextAirState    = StateMachine_None;
        self->nextGroundState = StateMachine_None;
        self->velocity.x      = 0;
        self->velocity.y      = 0;
        self->outtaHereTimer  = 0;
        if (config.useVoiceLines)
            RSDK.PlaySfx(outtaHereSfx, false, 255);
    }
}

bool32 Player_State_OuttaHere_Hook(bool32 skipped)
{
    RSDK_THIS(Player);

    if (!self->onGround) {
        if (self->sidekick && (self->velocity.y + self->gravityStrength) > 0x100000) {
            // Don't spawn the Game Over object
            destroyEntity(self);
            return true;
        }
        return false;
    }

    if (!config.useFrameID)
        return false;

    if (RSDK.GetFrameID(&self->animator)) {
        self->applyJumpCap = false;

        if (self->direction == FLIP_X)
            self->velocity.x = -0x10000;
        else
            self->velocity.x = 0x10000;
        self->velocity.y = -0x58000;

        self->onGround   = false;
        self->stateInput = StateMachine_None;

        if (self->camera)
            self->camera->state = StateMachine_None;
    }

    return true;
}

void Player_StageLoad(void)
{
    Mod.Super(Player->classID, SUPER_STAGELOAD, NULL);

    // Load SFX
    Mod_Player->sfxOuttahereT = RSDK.GetSfx("Global/OuttaHereT.wav");
    Mod_Player->sfxOuttahereK = RSDK.GetSfx("Global/OuttaHereK.wav");
#if MANIA_USE_PLUS
    Mod_Player->sfxOuttahereM = RSDK.GetSfx("Global/OuttaHereM.wav");
    Mod_Player->sfxOuttahereR = RSDK.GetSfx("Global/OuttaHereR.wav");
#endif
}