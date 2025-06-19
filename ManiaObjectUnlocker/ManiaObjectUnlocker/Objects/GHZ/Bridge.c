#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Bridge.h"

ObjectBridge *Bridge;

void Bridge_StageLoad(void)
{
    if (CheckUnlock("BridgeGHZ"))
        Bridge->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Bridge.bin", SCOPE_STAGE);
    else if (CheckUnlock("BridgeHCZ"))
        Bridge->aniFrames = RSDK.LoadSpriteAnimation("HCZ/Bridge.bin", SCOPE_STAGE);
    else if (CheckUnlock("BridgeLRZ1"))
        Bridge->aniFrames = RSDK.LoadSpriteAnimation("LRZ1/Bridge.bin", SCOPE_STAGE);

    Mod.Super(Bridge->classID, SUPER_STAGELOAD, NULL);
}
