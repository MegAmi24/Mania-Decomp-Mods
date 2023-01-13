#include "GameAPI/Game.h"
#include "ItemBox.h"
#include "HUD.h"
#include "../ModConfig.h"

ObjectItemBox *ItemBox;

void ItemBox_StageLoad(void)
{
    RSDK_THIS(ItemBox);

    Mod.Super(ItemBox->classID, SUPER_STAGELOAD, NULL);

    // Replace Hyper Ring sprite with heart
    SpriteFrame *dst = RSDK.GetFrame(ItemBox->aniFrames, 2, 11);
    SpriteFrame *src = RSDK.GetFrame(Mod_HUD->healthFrames, 2, 0);

    *dst = *src;
}

bool32 ItemBox_State_Break_Hook(bool32 skipped)
{
    RSDK_THIS(ItemBox);

    EntityPlayer *player = (EntityPlayer *)self->storedEntity;

    if (self->contentsSpeed < 0 && (self->contentsSpeed + 0x1800) >= 0) {
        switch (self->type) {
            case ITEMBOX_BLUESHIELD:
            case ITEMBOX_BUBBLESHIELD:
            case ITEMBOX_FIRESHIELD:
            case ITEMBOX_LIGHTNINGSHIELD:
                if (player->shield == self->type && player->health < config.MaxHealth)
                    player->health++;
                break;

            case ITEMBOX_HYPERRING:
                if (player->health < config.MaxHealth)
                    player->health++;
                break;

            default: break;
        }
    }

    return false;
}