#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Spikes.h"

ObjectSpikes *Spikes;

void Spikes_StageLoad(void)
{
    Mod.Super(Spikes->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("SpikesFBZ")) {
        Spikes->aniFrames = RSDK.LoadSpriteAnimation("FBZ/Spikes.bin", SCOPE_STAGE);
        Spikes->stateDraw = Mod.GetPublicFunction(NULL, "Spikes_Draw_Global");
    }
    else if (CheckUnlock("SpikesPSZ2")) {
        Spikes->aniFrames = RSDK.LoadSpriteAnimation("PSZ2/Spikes.bin", SCOPE_STAGE);
        Spikes->stateDraw = Mod.GetPublicFunction(NULL, "Spikes_Draw_Glint");
    }
}
