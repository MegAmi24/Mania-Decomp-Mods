#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Splats.h"

ObjectSplats *Splats;

void Splats_StageLoad(void)
{
    if (CheckUnlock("SplatsGHZ")) {
        Splats->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Splats.bin", SCOPE_STAGE);

        Splats->initialState = Mod.GetPublicFunction(NULL, "Splats_State_BounceAround");
    }
    else if (CheckUnlock("SplatsPSZ1")) {
        Splats->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/Splats.bin", SCOPE_STAGE);

        Splats->initialState = Mod.GetPublicFunction(NULL, "Splats_State_InkJarSpawner");
    }

    Mod.Super(Splats->classID, SUPER_STAGELOAD, NULL);
}
