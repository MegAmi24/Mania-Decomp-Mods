#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Blaster.h"

ObjectBlaster *Blaster;

void Blaster_StageLoad(void)
{
    if (CheckUnlock("Blaster"))
        Blaster->aniFrames = RSDK.LoadSpriteAnimation("FBZ/Blaster.bin", SCOPE_STAGE);

    Mod.Super(Blaster->classID, SUPER_STAGELOAD, NULL);
}
