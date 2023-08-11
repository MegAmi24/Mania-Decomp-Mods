#include "GameAPI/Game.h"
#include "Zone.h"
#include "Music.h"
#include <time.h>

ObjectZone *Zone;

void Zone_StaticUpdate(void)
{
    if (Zone->actID > 0)
        Music_SetMusicTrack("ActClear2.ogg", TRACK_ACTCLEAR, false);
    Mod.Super(Zone->classID, SUPER_STATICUPDATE, NULL);
}