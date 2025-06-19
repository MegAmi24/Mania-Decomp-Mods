#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "ConveyorWheel.h"

ObjectConveyorWheel *ConveyorWheel;

void ConveyorWheel_StageLoad(void)
{
    if (CheckUnlock("ConveyorWheel"))
        ConveyorWheel->aniFrames = RSDK.LoadSpriteAnimation("MMZ/ConveyorWheel.bin", SCOPE_STAGE);

    Mod.Super(ConveyorWheel->classID, SUPER_STAGELOAD, NULL);
}
