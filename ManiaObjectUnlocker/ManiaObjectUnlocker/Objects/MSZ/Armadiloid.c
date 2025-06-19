#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Armadiloid.h"

ObjectArmadiloid *Armadiloid;

void Armadiloid_StageLoad(void)
{
    if (CheckUnlock("Armadiloid"))
        Armadiloid->aniFrames = RSDK.LoadSpriteAnimation("MSZ/Armadiloid.bin", SCOPE_STAGE);

    Mod.Super(Armadiloid->classID, SUPER_STAGELOAD, NULL);
}
