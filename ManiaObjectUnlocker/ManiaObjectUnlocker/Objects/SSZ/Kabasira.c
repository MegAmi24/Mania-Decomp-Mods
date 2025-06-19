#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Kabasira.h"

ObjectKabasira *Kabasira;

void Kabasira_StageLoad(void)
{
    if (CheckUnlock("KabasiraSSZ1"))
        Kabasira->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/Kabasira.bin", SCOPE_STAGE);\

    Mod.Super(Kabasira->classID, SUPER_STAGELOAD, NULL);
}
