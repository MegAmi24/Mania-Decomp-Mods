#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Fan.h"

ObjectFan *Fan;

void Fan_StageLoad(void)
{
    if (CheckUnlock("FanOOZ")) {
        Fan->aniFrames = RSDK.LoadSpriteAnimation("OOZ/Fan.bin", SCOPE_STAGE);

        Fan->hitboxTop.left  = -64;
        Fan->hitboxTop.right = 64;

        Fan->unused      = 5;
        Fan->minVelocity = -0x50000;

        Fan->hitboxBottom.left   = -16;
        Fan->hitboxBottom.right  = 16;
        Fan->hitboxBottom.top    = -160;
        Fan->hitboxBottom.bottom = 32;

        Fan->hitboxSides.top    = -160;
        Fan->hitboxSides.bottom = 112;
        Fan->hitboxSides.left   = -112;
        Fan->hitboxSides.right  = 32;
    }
    else if (CheckUnlock("FanHCZ")) {
        Fan->aniFrames = RSDK.LoadSpriteAnimation("HCZ/Fan.bin", SCOPE_STAGE);

        Fan->hitboxTop.left  = -16;
        Fan->hitboxTop.right = 16;

        Fan->unused      = 20;
        Fan->minVelocity = -0x20000;

        Fan->hitboxBottom.left   = -16;
        Fan->hitboxBottom.right  = 16;
        Fan->hitboxBottom.top    = -160;
        Fan->hitboxBottom.bottom = 32;

        Fan->hitboxSides.top    = -24;
        Fan->hitboxSides.bottom = 24;
        Fan->hitboxSides.left   = -112;
        Fan->hitboxSides.right  = 32;

        Fan->sfxFan = RSDK.GetSfx("HCZ/SmallFan.wav");
        Fan->active = ACTIVE_ALWAYS;
    }

    Mod.Super(Fan->classID, SUPER_STAGELOAD, NULL);
}
