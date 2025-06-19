#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Water.h"

ObjectWater *Water;

void Water_StageLoad(void)
{
    Mod.Super(Water->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("Water")) {
        Water->wakeFrames      = RSDK.LoadSpriteAnimation("HCZ/Wake.bin", SCOPE_STAGE);
        Water->bigBubbleFrames = RSDK.LoadSpriteAnimation("HCZ/BigBubble.bin", SCOPE_STAGE);

        Water->sfxWaterLevelL = RSDK.GetSfx("HCZ/WaterLevel_L.wav");
        Water->sfxWaterLevelR = RSDK.GetSfx("HCZ/WaterLevel_R.wav");
        Water->sfxDNAGrab     = RSDK.GetSfx("CPZ/DNAGrab.wav");
        Water->sfxDNABurst    = RSDK.GetSfx("CPZ/DNABurst.wav");

        RSDK.SetSpriteAnimation(Water->wakeFrames, 0, &Water->wakeAnimator, true, 0);
    }
}
