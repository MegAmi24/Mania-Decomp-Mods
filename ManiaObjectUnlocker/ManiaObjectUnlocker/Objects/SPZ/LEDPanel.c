#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "LEDPanel.h"

ObjectLEDPanel *LEDPanel;

void LEDPanel_StageLoad(void)
{
    if (CheckUnlock("LEDPanel"))
        LEDPanel->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/LED.bin", SCOPE_STAGE);

    Mod.Super(LEDPanel->classID, SUPER_STAGELOAD, NULL);
}
