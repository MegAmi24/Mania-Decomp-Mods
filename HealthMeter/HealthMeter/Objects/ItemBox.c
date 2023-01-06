#include "GameAPI/Game.h"
#include "ItemBox.h"
#include "../ModConfig.h"

ObjectItemBox *ItemBox;

bool32 ItemBox_State_Break_Hook(bool32 skipped)
{
    RSDK_THIS(ItemBox);

    EntityPlayer *player           = (EntityPlayer *)self->storedEntity;
    ObjectLRZConvItem *LRZConvItem = Mod.FindObject("LRZConvItem");

    if (LRZConvItem && self->lrzConvPhys)
        LRZConvItem_HandleLRZConvPhys(self);
    else
        ItemBox_HandleFallingCollision();

    if (self->contentsSpeed < 0) {
        self->contentsPos.y += self->contentsSpeed;
        self->contentsSpeed += 0x1800;
    }

    if (self->contentsSpeed >= 0) {
        self->contentsSpeed = 0;

        switch (self->type) {
            case ITEMBOX_BLUESHIELD:
            case ITEMBOX_BUBBLESHIELD:
            case ITEMBOX_FIRESHIELD:
            case ITEMBOX_LIGHTNINGSHIELD:
                if (player->shield == self->type && player->health < config.MaxHealth)
                    player->health++;
                ItemBox_GivePowerup();
                break;

            case ITEMBOX_HYPERRING:
                RSDK.PlaySfx(ItemBox->sfxHyperRing, false, 255);
                if (player->health < config.MaxHealth)
                    player->health++;
                break;

            default: ItemBox_GivePowerup(); break;
        }

        RSDK.SetSpriteAnimation(ItemBox->aniFrames, 5, &self->contentsAnimator, true, 0);
        self->state = ItemBox_State_IconFinish;
    }

    return true;
}