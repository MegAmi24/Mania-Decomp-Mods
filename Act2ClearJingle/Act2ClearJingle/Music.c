#include "GameAPI/Game.h"
#include "Music.h"

ObjectMusic *Music;

void Music_StageLoad(void)
{
    Mod.Super(Music->classID, SUPER_STAGELOAD, NULL);

    if (Mod.FindObject("Zone")) {
        if (Zone_IsZoneLastAct())
            Music_SetMusicTrack("ActClear2.ogg", TRACK_ACTCLEAR, false);
    }
}