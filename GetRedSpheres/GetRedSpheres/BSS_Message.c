#include "GameAPI/Game.h"
#include "BSS_Message.h"
#include "ModConfig.h"

ObjectBSS_Message *BSS_Message;
ModObjectBSS_Message *Mod_BSS_Message;

void BSS_Message_StageLoad(void)
{
    Mod.Super(BSS_Message->classID, SUPER_STAGELOAD, NULL);

    Mod_BSS_Message->redFrames = RSDK.LoadSpriteAnimation("SpecialBS/GetRedSpheres.bin", SCOPE_STAGE);

    if (config.alwaysGetRed || GET_CHARACTER_ID(1) == ID_KNUCKLES) {
        // Replace Get Blue with Get Red
        SpriteFrame *blueMessage = RSDK.GetFrame(BSS_Message->aniFrames, 2, 0);
        SpriteFrame *redMessage = RSDK.GetFrame(Mod_BSS_Message->redFrames, 0, 0);

        *blueMessage = *redMessage;
    }
}