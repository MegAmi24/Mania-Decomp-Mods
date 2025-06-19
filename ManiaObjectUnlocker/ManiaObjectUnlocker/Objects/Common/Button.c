#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Button.h"

ObjectButton *Button;

void Button_StageLoad(void)
{
    Mod.Super(Button->classID, SUPER_STAGELOAD, NULL);

    if (!RSDK.CheckSceneFolder("MMZ") && !RSDK.CheckSceneFolder("FBZ") && !RSDK.CheckSceneFolder("LRZ1") && !RSDK.CheckSceneFolder("LRZ2")
        && !RSDK.CheckSceneFolder("HCZ") && !RSDK.CheckSceneFolder("TMZ3")) {
        if (CheckUnlock("ButtonMMZ")) {
            Button->aniFrames    = RSDK.LoadSpriteAnimation("MMZ/Button.bin", SCOPE_STAGE);
            Button->activatePos  = TO_FIXED(8);
            Button->buttonOffset = TO_FIXED(5);
            Button->hitboxOffset = 13;
            Button->unused1      = 5;
        }
        else if (CheckUnlock("ButtonFBZ")) {
            Button->aniFrames    = RSDK.LoadSpriteAnimation("FBZ/Button.bin", SCOPE_STAGE);
            Button->activatePos  = TO_FIXED(8);
            Button->buttonOffset = TO_FIXED(5);
            Button->hitboxOffset = 13;
            Button->unused1      = 5;
        }
        else if (CheckUnlock("ButtonLRZ1")) {
            Button->aniFrames    = RSDK.LoadSpriteAnimation("LRZ1/Button.bin", SCOPE_STAGE);
            Button->activatePos  = TO_FIXED(4);
            Button->buttonOffset = TO_FIXED(3);
            Button->hitboxOffset = 7;
            Button->unused1      = 3;
        }
        else if (CheckUnlock("ButtonHCZ")) {
            Button->aniFrames    = RSDK.LoadSpriteAnimation("HCZ/Button.bin", SCOPE_STAGE);
            Button->activatePos  = TO_FIXED(3);
            Button->buttonOffset = TO_FIXED(3);
            Button->hitboxOffset = 9;
            Button->unused1      = 6;
        }
        else if (CheckUnlock("ButtonTMZ3")) {
            Button->aniFrames    = RSDK.LoadSpriteAnimation("TMZ1/Button.bin", SCOPE_STAGE);
            Button->activatePos  = TO_FIXED(3);
            Button->buttonOffset = TO_FIXED(3);
            Button->hitboxOffset = 9;
            Button->unused1      = 6;
        }
    }
}
