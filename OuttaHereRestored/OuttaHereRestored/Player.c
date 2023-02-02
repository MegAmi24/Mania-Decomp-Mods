#include "GameAPI/Game.h"
#include "Player.h"
#include "ModConfig.h"

ObjectPlayer *Player;
ModObjectPlayer *Mod_Player;

void Player_SetOuttaHere(void)
{
    RSDK_THIS(Player);

    // Check for character related things
    uint16 outtaHereSfx = Player->sfxOuttahere;
    bool32 canOuttaHere = false;
    switch (self->characterID) {
        case ID_SONIC: canOuttaHere = true; break;
        case ID_TAILS:
            if (config.tailsOuttaHere)
                canOuttaHere = true;
            if (config.uniqueCharSfx)
                outtaHereSfx = Mod_Player->sfxOuttahereT;
            break;

        case ID_KNUCKLES:
            if (config.knuxOuttaHere)
                canOuttaHere = true;
            if (config.uniqueCharSfx)
                outtaHereSfx = Mod_Player->sfxOuttahereK;
            break;

#if MANIA_USE_PLUS
        case ID_MIGHTY:
            if (config.mightyOuttaHere)
                canOuttaHere = true;
            if (config.uniqueCharSfx)
                outtaHereSfx = Mod_Player->sfxOuttahereM;
            break;

        case ID_RAY:
            if (config.rayOuttaHere)
                canOuttaHere = true;
            if (config.uniqueCharSfx)
                outtaHereSfx = Mod_Player->sfxOuttahereR;
            break;
#endif
    }

    // Wait for ~3 minutes to do outta here
    if (canOuttaHere && (self->outtaHereTimer >= 10620 || (SKU->platform == PLATFORM_DEV && ControllerInfo[self->controllerID].keyZ.press))) {
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_OUTTA_HERE, &self->animator, false, 0);
        self->state           = Player_State_OuttaHere;
        self->tileCollisions  = TILECOLLISION_NONE;
        self->interaction     = false;
        self->nextAirState    = StateMachine_None;
        self->nextGroundState = StateMachine_None;
        self->velocity.x      = 0;
        self->velocity.y      = 0;
        RSDK.PlaySfx(outtaHereSfx, false, 255);
    }
}

bool32 Player_State_OuttaHere_Hook(bool32 skipped)
{
    RSDK_THIS(Player);

    if (self->onGround) {
        if (self->animator.frameID
            == (self->characterID == ID_SONIC && self->superState == SUPERSTATE_SUPER && config.superSonicOuttaHere ? 22 : 14)) {
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
    }
    else {
        Player_HandleAirMovement();
        if (self->velocity.y > 0x100000) {
            ObjectGameOver *GameOver = Mod.FindObject("GameOver");
            RSDK.ResetEntitySlot(SLOT_GAMEOVER, GameOver->classID, INT_TO_VOID(false));
            destroyEntity(self);
        }
    }

    return true;
}

void Player_StageLoad(void)
{
    Mod.Super(Player->classID, SUPER_STAGELOAD, NULL);

    // Load SFX
    Mod_Player->sfxOuttahereT = RSDK.GetSfx("OuttaHere/OuttaHereT.wav");
    Mod_Player->sfxOuttahereK = RSDK.GetSfx("OuttaHere/OuttaHereK.wav");
#if MANIA_USE_PLUS
    Mod_Player->sfxOuttahereM = RSDK.GetSfx("OuttaHere/OuttaHereM.wav");
    Mod_Player->sfxOuttahereR = RSDK.GetSfx("OuttaHere/OuttaHereR.wav");
#endif
}