#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "ConveyorBelt.h"

ObjectConveyorBelt *ConveyorBelt;

void ConveyorBelt_StageLoad(void)
{
    if (CheckUnlock("ConveyorBelt"))
        ConveyorBelt->aniFrames = RSDK.LoadSpriteAnimation("MMZ/ConveyorWheel.bin", SCOPE_STAGE);

    Mod.Super(ConveyorBelt->classID, SUPER_STAGELOAD, NULL);
}
