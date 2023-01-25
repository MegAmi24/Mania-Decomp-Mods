#include "GameAPI/Game.h"
#include "PullChain.h"
#include "HandLauncher.h"
#include "Player.h"

ObjectPullChain *PullChain;

void PullChain_Update(void)
{
    RSDK_THIS(PullChain);

    if (!self->decorMode) {
        ObjectPlayer *Player = Mod.FindObject("Player");
        foreach_active(Player, player)
        {
            int32 playerID = RSDK.GetEntitySlot(player);

            if ((1 << playerID) & self->activePlayers) {
                if (!player->sidekick && PullChain_HandleDunkeyCode(player)) {
                    ObjectHandLauncher *HandLauncher = Mod.FindObject("HandLauncher");
                    HandLauncher->dunkeyMode         = true;
                    ObjectRing *Ring = Mod.FindObject("Ring");
                    RSDK.PlaySfx(Ring->sfxRing, false, 0xFF);
                }
            }
        }
    }

    Mod.Super(PullChain->classID, SUPER_UPDATE, NULL);
}

bool32 PullChain_HandleDunkeyCode(EntityPlayer *player)
{
    RSDK_THIS(PullChain);

    ObjectHandLauncher *HandLauncher = Mod.FindObject("HandLauncher");
    if (HandLauncher->dunkeyMode)
        return false;

    uint8 buttonMasks = PULLCHAIN_INPUT_NONE;
    if (player->left)
        buttonMasks = 1;

    if (player->right)
        buttonMasks |= 2;

    if (player->up)
        buttonMasks |= 4;

    if (player->down)
        buttonMasks |= 8;

    if (buttonMasks == self->codeButtonMasks)
        return false;

    for (int32 i = 1; i < 18; ++i) self->cheatCodeInputs[i - 1] = self->cheatCodeInputs[i];

    self->cheatCodeInputs[17] = PULLCHAIN_INPUT_NONE;
    if (player->left)
        self->cheatCodeInputs[17] = PULLCHAIN_INPUT_LEFT;
    else if (player->right)
        self->cheatCodeInputs[17] = PULLCHAIN_INPUT_RIGHT;
    else if (player->up)
        self->cheatCodeInputs[17] = PULLCHAIN_INPUT_UP;
    else if (player->down)
        self->cheatCodeInputs[17] = PULLCHAIN_INPUT_DOWN;

    bool32 activatedCheatCode = true;
    for (int32 i = 0; i < 18; ++i) activatedCheatCode &= (self->cheatCodeInputs[i] == PullChain->dunkeyCode[i]);
    self->codeButtonMasks = buttonMasks;

    return activatedCheatCode;
}
