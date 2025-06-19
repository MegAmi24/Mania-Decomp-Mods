#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "IceBomba.h"

ObjectIceBomba *IceBomba;

void IceBomba_StageLoad(void)
{
    if (CheckUnlock("IceBombaPSZ1")) // PGZ1 doesn't have this badnik anywhere, the anim file doesn't even exist in the files...
        IceBomba->aniFrames = RSDK.LoadSpriteAnimation("PSZ1/IceBomba.bin", SCOPE_STAGE);

    Mod.Super(IceBomba->classID, SUPER_STAGELOAD, NULL);
}
