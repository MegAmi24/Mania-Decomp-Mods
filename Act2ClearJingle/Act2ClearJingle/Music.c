#include "GameAPI/Game.h"
#include "Music.h"
#include "ActClear.h"

void (*Music_SetMusicTrack)(const char *path, uint8 track, uint32 loopPoint) = NULL;

ObjectMusic *Music;

void Music_StaticUpdate(void)
{
    Mod.Super(Music->classID, SUPER_STATICUPDATE, NULL);

    if (RSDK.FindObject("Zone")) {
        if (Zone_IsZoneLastAct()) {
            ObjectActClear *ActClear = Mod.FindObject("ActClear");
            if (ActClear) {
                // Check if in an outro to an Act 1 (PGZ/OOZ)
                // For some reason I can't get a check for the full track name working, everything I've tried just crashes the game
                if (Music->trackNames[TRACK_ACTCLEAR][8] == '2' && ActClear->displayedActID == 1)
                    Music_SetMusicTrack("ActClear.ogg", TRACK_ACTCLEAR, false);
                else if (ActClear->finished) // Set the track back after the results
                    Music_SetMusicTrack("ActClear2.ogg", TRACK_ACTCLEAR, false);
            }
        }
    }
}

void Music_StageLoad(void)
{
    Mod.Super(Music->classID, SUPER_STAGELOAD, NULL);

    if (RSDK.FindObject("Zone")) {
        if (Zone_IsZoneLastAct())
            Music_SetMusicTrack("ActClear2.ogg", TRACK_ACTCLEAR, false);
    }
}