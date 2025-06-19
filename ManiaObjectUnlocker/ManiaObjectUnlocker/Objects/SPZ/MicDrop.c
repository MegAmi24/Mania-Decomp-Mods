#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "MicDrop.h"

ObjectMicDrop *MicDrop;

void MicDrop_StageLoad(void)
{
    Mod.Super(MicDrop->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("MicDropSPZ1"))
        MicDrop->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/MicDrop.bin", SCOPE_STAGE);
}
