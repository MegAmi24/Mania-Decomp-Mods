#ifndef OBJ_GAMEPROGRESS_H
#define OBJ_GAMEPROGRESS_H

#include "GameAPI/Game.h"

#define GAMEPROGRESS_MEDAL_COUNT   (32)
#define GAMEPROGRESS_ZONE_COUNT    (12)
#define GAMEPROGRESS_EMERALD_COUNT (7)

typedef enum {
    GAMEPROGRESS_UNLOCK_TIMEATTACK,
    GAMEPROGRESS_UNLOCK_COMPETITION,
    GAMEPROGRESS_UNLOCK_PEELOUT,
    GAMEPROGRESS_UNLOCK_INSTASHIELD,
    GAMEPROGRESS_UNLOCK_ANDKNUX,
    GAMEPROGRESS_UNLOCK_DEBUGMODE,
    GAMEPROGRESS_UNLOCK_MEANBEAN,
    GAMEPROGRESS_UNLOCK_DAGARDEN,
    GAMEPROGRESS_UNLOCK_BLUESPHERES,
    GAMEPROGRESS_UNLOCK_COUNT,
} GameProgressUnlockIDs;

typedef enum {
    GAMEPROGRESS_ENDING_NONE,
    GAMEPROGRESS_ENDING_BAD,
    GAMEPROGRESS_ENDING_GOOD,
} GameProgressEndingIDs;

typedef enum {
    GAMEPROGRESS_MEDAL_NONE,
    GAMEPROGRESS_MEDAL_SILVER,
    GAMEPROGRESS_MEDAL_GOLD,
    GAMEPROGRESS_MEDAL_ID_COUNT,
} GameProgressMedalIDs;

// Using a seperate ProgressRAM struct
// Normally (and officially) the ObjectGameProgress struct was used here
// but due to v5U updating the entity (and thus the ProgressRAM "spec")
// ObjectGameProgress is no longer easily compatible across versions
// so I gave it dummy data and will be using this struct to interact with progressRAM
// this one was also broken with plus since medals[] were aligned by 1 byte
// so when "filter" was added, all medals were offset by 1 without this fix
typedef struct {
    uint8 padding[0x56]; // aka sizeof(Entity) for pre-plus

    uint8 medals[GAMEPROGRESS_MEDAL_COUNT];
    bool32 allGoldMedals;
    bool32 allSilverMedals;
    bool32 zoneCleared[GAMEPROGRESS_ZONE_COUNT];
    bool32 allZonesCleared;
    bool32 emeraldObtained[GAMEPROGRESS_EMERALD_COUNT];
    bool32 allEmeraldsObtained;
    bool32 unreadNotifs[GAMEPROGRESS_UNLOCK_COUNT];
    bool32 specialCleared[GAMEPROGRESS_EMERALD_COUNT];
    bool32 allSpecialCleared;
    bool32 unlockedEndingID;
    int32 goldMedalCount;
    int32 silverMedalCount;
} ProgressRAM;

// Object Class
typedef struct {
    RSDK_OBJECT
} ObjectGameProgress;

// Entity Class
typedef struct {
    RSDK_ENTITY
    // padding to match whatever it would be normally
    // not required, but its for safety :)
    uint8 padding[sizeof(ProgressRAM) - sizeof(Entity)];
} EntityGameProgress;

// Object Struct
extern ObjectGameProgress *GameProgress;

// Extra Entity Events
extern ProgressRAM *(*GameProgress_GetProgressRAM)(void);
extern void (*GameProgress_ClearBSSSave)(void);
extern void (*GameProgress_MarkZoneCompleted)(int32 zoneID);
extern void (*GameProgress_GiveEmerald)(int32 emeraldID);
extern void (*GameProgress_GiveEnding)(uint8 ending);
extern void (*GameProgress_GiveMedal)(uint8 medalID, uint8 type);

#endif //! OBJ_GAMEPROGRESS_H
