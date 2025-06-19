#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Decoration.h"

ObjectDecoration *Decoration;

void Decoration_StageLoad(void)
{
    if (CheckUnlock("DecorationGHZ"))
        Decoration->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Decoration.bin", SCOPE_STAGE);
    else if (CheckUnlock("DecorationMSZEnding"))
        Decoration->aniFrames = RSDK.LoadSpriteAnimation("MSZ/Ending.bin", SCOPE_STAGE);

    Mod.Super(Decoration->classID, SUPER_STAGELOAD, NULL);
}
