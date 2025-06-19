#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "ButtonDoor.h"

ObjectButtonDoor *ButtonDoor;

void ButtonDoor_StageLoad(void)
{
    if (CheckUnlock("ButtonDoorLRZ1")) {
        ButtonDoor->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/ButtonDoor.bin", SCOPE_STAGE);
        ButtonDoor->sfxOpen   = RSDK.GetSfx("Stage/Open.wav");
    }
    else if (CheckUnlock("ButtonDoorHCZ")) {
        ButtonDoor->aniFrames = RSDK.LoadSpriteAnimation("HCZ/ButtonDoor.bin", SCOPE_STAGE);
        ButtonDoor->sfxOpen   = RSDK.GetSfx("Stage/Clack.wav");
    }

    Mod.Super(ButtonDoor->classID, SUPER_STAGELOAD, NULL);
}
