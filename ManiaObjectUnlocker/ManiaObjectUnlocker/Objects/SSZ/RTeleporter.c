#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "RTeleporter.h"

ObjectRTeleporter *RTeleporter;

void RTeleporter_StageLoad(void)
{
    if (CheckUnlock("RTeleporterSSZ"))
        RTeleporter->aniFrames = RSDK.LoadSpriteAnimation("SSZ/RTeleporter.bin", SCOPE_STAGE);

    Mod.Super(RTeleporter->classID, SUPER_STAGELOAD, NULL);
}
