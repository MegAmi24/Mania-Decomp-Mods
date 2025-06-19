#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "SpeedBooster.h"

ObjectSpeedBooster *SpeedBooster;

void SpeedBooster_StageLoad(void)
{
    if (CheckUnlock("SpeedBoosterCPZ")) {
        SpeedBooster->aniFrames = RSDK.LoadSpriteAnimation("CPZ/SpeedBooster.bin", SCOPE_STAGE);

        SpeedBooster->hitbox.left   = -16;
        SpeedBooster->hitbox.top    = -16;
        SpeedBooster->hitbox.right  = 16;
        SpeedBooster->hitbox.bottom = 16;

        SpeedBooster->sfxSpeedBooster = RSDK.GetSfx("Global/Spring.wav");

        SpeedBooster->defaultState = Mod.GetPublicFunction(NULL, "SpeedBooster_State_SpeedBooster");
    }
    else if (CheckUnlock("SpeedBoosterSSZ1") || CheckUnlock("SpeedBoosterSSZ2")) {
        if (CheckUnlock("SpeedBoosterSSZ1"))
            SpeedBooster->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/SpeedBooster.bin", SCOPE_STAGE);
        else
            SpeedBooster->aniFrames = RSDK.LoadSpriteAnimation("SSZ2/SpeedBooster.bin", SCOPE_STAGE);

        SpeedBooster->hitbox.left   = -32;
        SpeedBooster->hitbox.top    = -16;
        SpeedBooster->hitbox.right  = 32;
        SpeedBooster->hitbox.bottom = 0;

        SpeedBooster->sfxSpeedBooster = RSDK.GetSfx("Stage/SpeedBooster.wav");

        SpeedBooster->defaultState = Mod.GetPublicFunction(NULL, "SpeedBooster_State_SSZFire");
    }

    Mod.Super(SpeedBooster->classID, SUPER_STAGELOAD, NULL);
}
