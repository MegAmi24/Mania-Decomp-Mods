#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "FilmReel.h"

ObjectFilmReel *FilmReel;

void FilmReel_StageLoad(void)
{
    Mod.Super(FilmReel->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("FilmReelSPZ1"))
        FilmReel->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/FilmReel.bin", SCOPE_STAGE);
}
