#include "GameAPI/Game.h"
#include "BSS_HUD.h"
#include "ModConfig.h"

ObjectBSS_HUD *BSS_HUD;
ModObjectBSS_HUD *Mod_BSS_HUD;

void BSS_HUD_StageLoad(void)
{
    Mod.Super(BSS_HUD->classID, SUPER_STAGELOAD, NULL);

    Mod_BSS_HUD->redFrames = RSDK.LoadSpriteAnimation("SpecialBS/GetRedSpheres.bin", SCOPE_STAGE);

    if (config.alwaysGetRed || GET_CHARACTER_ID(1) == ID_KNUCKLES) {
        // Replace Blue Sphere HUD with Red Sphere
        SpriteFrame *blueHUD = RSDK.GetFrame(BSS_HUD->aniFrames, 0, 0);
        SpriteFrame *redHUD = RSDK.GetFrame(Mod_BSS_HUD->redFrames, 1, 0);

        *blueHUD = *redHUD;
    }
}
