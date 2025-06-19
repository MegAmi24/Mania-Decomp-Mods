#include "UnlockCodes.h"

char activeUnlocks[UNLOCK_MAX][MAX_LEN];
int32 unlockedCount;

// clang-format off

// All supported unlock codes
// The addresses are offsets from where the EXE code starts, which, at least for me on Steam 1.06, is B80000 in Cheat Engine
// If you'd like to make a pull request to add any more codes, please specify the object (and which lock if the object has multiple locks) and version of Mania each code is for
static UnlockCode unlockCodes[] = {
    ///////////////////
    // VERSION 1.06
    ///////////////////

    // GHZ
    { .code = "writenop 000D9780 2", .unlock = "Batbrain" },
    { .code = "writenop 0000D2B0 2", .unlock = "BridgeGHZ" },
    { .code = "writenop 000E9461 2", .unlock = "BuzzBomberGHZ" },
    { .code = "writenop 000F09E1 2", .unlock = "CheckerBallGHZ" },
    { .code = "writenop 000EDBB0 2", .unlock = "Chopper" },
    { .code = "writenop 000EE6A0 2", .unlock = "Crabmeat" },
    { .code = "writenop 00067101 2", .unlock = "DecorationGHZ" },
    { .code = "writenop 0000CCE1 2", .unlock = "Fireball" },
    { .code = "writenop 000EECA1 2", .unlock = "MotobugGHZ" },
    { .code = "writenop 000EF4A1 2", .unlock = "Newtron" },
    { .code = "writenop 0008AB6A 2", .unlock = "PlatformGHZ" },
    { .code = "writenop 00188291 2", .unlock = "SpikeLog" },
    { .code = "writenop 000EFE70 2", .unlock = "SplatsGHZ" },
    { .code = "writenop 001A6541 2", .unlock = "ZipLine" },

    // CPZ
    { .code = "writenop 000D6BA0 2", .unlock = "Ball" },
    { .code = "writenop 000DE130 2", .unlock = "Bubbler" },
    { .code = "writenop 000ED386 2", .unlock = "CaterkillerJrCPZ" },
    { .code = "writenop 001604DD 2", .unlock = "OneWayDoorCPZ" },
    { .code = "writenop 00133880 2", .unlock = "SpeedBoosterCPZ" },
    { .code = "writenop 001909AD 2", .unlock = "SweepCPZ" },
    { .code = "writenop 001952C6 2", .unlock = "TubeSpringCPZ" },

    // SPZ1
    { .code = "writenop 0007D824 2", .unlock = "CutsceneHBHSPZ1Boss" },
    { .code = "writenop 000EB5E0 2", .unlock = "CanistaSPZ1" },
    { .code = "writenop 000F2A40 2", .unlock = "CircleBumperSPZ1" },
    { .code = "writenop 000F33A4 2", .unlock = "ClapperboardSPZ1" },
    { .code = "writenop 0010F681 2", .unlock = "DirectorChair" },
    { .code = "writenop 00126482 2", .unlock = "FilmReelSPZ1" },
    { .code = "writenop 0014F951 2", .unlock = "LEDPanel" },
    { .code = "writenop 0015BDD2 2", .unlock = "MicDropSPZ1" },
    { .code = "writenop 00176114 2", .unlock = "RockemSockemSPZ1" },
    { .code = "writenop 00180122 2", .unlock = "ShutterbugSPZ1" },
    { .code = "writenop 00195B02 2", .unlock = "TubinautSPZ1" },

    // SPZ2
    { .code = "writenop 000EB5FB 2", .unlock = "CanistaSPZ2" },
    { .code = "writenop 00162E71 2", .unlock = "PathInverter" },

    // FBZ
    { .code = "writenop 00025780 2", .unlock = "Blaster" },
    { .code = "writenop 00086670 2", .unlock = "ButtonFBZ" },
    { .code = "writenop 0001C4E2 2", .unlock = "CurrentFBZ" },
    { .code = "writenop 0011B44A 2", .unlock = "ElectroMagnet" },
    { .code = "writenop 00128AD1 2", .unlock = "FlameSpring" },
    { .code = "writenop 001230A9 2", .unlock = "HangGliderFBZ" },
    { .code = "writenop 00088C50 2", .unlock = "HangPoint" },
    { .code = "writenop 0011B261 2", .unlock = "MagSpikeBall" },
    { .code = "writenop 000A06AD 2", .unlock = "SpikesFBZ" },
    { .code = "writenop 00024ED0 2", .unlock = "Technosqueek" },
    { .code = "writenop 001952F2 2", .unlock = "TubeSpringFBZ" },
    { .code = "writenop 00196FA6 2", .unlock = "Tuesday" },
    { .code = "writenop 0019C841 2", .unlock = "TwistingDoor" },

    // PGZ1
    { .code = "writenop 000CF0A0 2", .unlock = "Acetone" },
    { .code = "writenop 00090EC0 2", .unlock = "Crate" },
    { .code = "writenop 00111F31 2", .unlock = "DoorTrigger" },
    { .code = "writenop 001121F0 2", .unlock = "DragonflyPSZ1" },
    { .code = "writenop 0012B660 2", .unlock = "FrostThrowerPSZ1" },
    { .code = "writenop 000A1C00 2", .unlock = "IcePSZ1" },
    { .code = "writenop 001452C0 2", .unlock = "IceBombaPSZ1" },
    { .code = "writenop 000CEE81 2", .unlock = "Ink" },
    { .code = "writenop 00145D51 2", .unlock = "InkWipe" },
    { .code = "writenop 00147716 2", .unlock = "JuggleSawPSZ1" },
    { .code = "writenop 00111811 2", .unlock = "PSZDoor" },
    { .code = "writenop 00167EE0 2", .unlock = "PetalPilePSZ1" },
    { .code = "writenop 0009F6E1 2", .unlock = "Press" },
    { .code = "writenop 0016CDD0 2", .unlock = "PrintBlock" },
    { .code = "writenop 00181507 2", .unlock = "SP500" },
    { .code = "writenop 000EFEA7 2", .unlock = "SplatsPSZ1" },
    { .code = "writenop 001A48C0 2", .unlock = "WoodrowPSZ1" },

    // PGZ2
    { .code = "writenop 0012B67B 2", .unlock = "FrostThrowerPSZ2" },
    { .code = "writenop 0007D857 2", .unlock = "CutsceneHBHShinobi" },
    { .code = "writenop 000A06CB 2", .unlock = "SpikesPSZ2" },
    { .code = "writenop 00167EFB 2", .unlock = "PetalPilePSZ2" },

    // SSZ1
    { .code = "writenop 00101E41 2",  .unlock = "DangoSSZ1" },
    { .code = "writenop 0012A600 2",  .unlock = "FlowerPod" },
    { .code = "writenop 00140E71 2",  .unlock = "HotaruSSZ1" },
    { .code = "writenop 00144367 2",  .unlock = "HotaruMKIISSZ1" },
    { .code = "writenop 00148850 2",  .unlock = "JunctionWheel" },
    { .code = "writenop 00148BA1 2",  .unlock = "KabasiraSSZ1" },
    { .code = "writenop 00149440 2",  .unlock = "KanabunSSZ1" },
    { .code = "writenop 0014A5A1 2",  .unlock = "LaunchSpringSSZ1" },
    { .code = "writenop 00134077 2",  .unlock = "MSHologramSSZ1" },
    { .code = "writenop 00177B2F 2",  .unlock = "RotatingSpikesSSZ1" },
    { .code = "writenop 00178DB4 13", .unlock = "RTeleporterSSZ" },
    { .code = "writenop 001A58B0 2",  .unlock = "YoyoPulley" },
    { .code = "writenop 00182C83 2",  .unlock = "SparkRailSSZ1" },
    { .code = "writenop 0013392A 2",  .unlock = "SpeedBoosterSSZ1" },
    { .code = "writenop 0018E379 2",  .unlock = "SSZSpikeBallSSZ1" },

    // SSZ2
    { .code = "writenop 001366F1 2", .unlock = "MSOrb" },
    { .code = "writenop 00133912 6", .unlock = "SpeedBoosterSSZ2" },

    // HCZ
    { .code = "writenop 000DB500 2", .unlock = "Blastoid" },
    { .code = "writenop 0000D2DC 2", .unlock = "BridgeHCZ" },
    { .code = "writenop 00086707 2", .unlock = "ButtonHCZ" },
    { .code = "writenop 000E8DDF 2", .unlock = "ButtonDoorHCZ" },
    { .code = "writenop 00105416 2", .unlock = "DiveEggman" },
    { .code = "writenop 00108426 2", .unlock = "DCEvent" },
    { .code = "writenop 0012193E 6", .unlock = "FanHCZ" },
    { .code = "writenop 00146560 2", .unlock = "Jawz" },
    { .code = "writenop 00146AAB 2", .unlock = "JellygniteHCZ" },
    { .code = "writenop 00158CE0 2", .unlock = "MegaChopper" },
    { .code = "writenop 0016B8F0 2", .unlock = "Pointdexter" },
    { .code = "writenop 001064B6 2", .unlock = "ScrewMobile" },
    { .code = "writenop 001989D1 2", .unlock = "TurboSpiker" },
    { .code = "writenop 000196E9 2", .unlock = "Water" },

    // MSZ
    { .code = "writenop 0006A530 2", .unlock = "Armadiloid" },
    { .code = "writenop 000E74D0 2", .unlock = "Bumpalo" },
    { .code = "writenop 000EAF86 2", .unlock = "Cactula" },
    { .code = "writenop 0006723C 2", .unlock = "DecorationMSZEnding" },
    { .code = "writenop 0007D8B3 6", .unlock = "CutsceneHBHHeavyMystic" },
    { .code = "writenop 0007D95C 6", .unlock = "CutsceneHBHRoguesFang" },
    { .code = "writenop 0007D976 6", .unlock = "CutsceneHBHRoguesBean" },
    { .code = "writenop 0007D9AD 6", .unlock = "CutsceneHBHRoguesBark" },
    { .code = "writenop 00176480 2", .unlock = "RollerMKII" },
    { .code = "writenop 00177B01 2", .unlock = "RotatingSpikesMSZ" },
    { .code = "writenop 00191910 2", .unlock = "SwingRopeMSZ" },
    { .code = "writenop 00067784 2", .unlock = "Tornado" },

    // OOZ
    { .code = "writenop 000D6154 2", .unlock = "Aquis" },
    { .code = "writenop 00121A0E 6", .unlock = "FanOOZ" },
    { .code = "writenop 0015FC44 2", .unlock = "Octus" },
    { .code = "writenop 001709C4 0", .unlock = "PullSwitch" },
    { .code = "writenop 00170BD4 2", .unlock = "PushSpring" },
    { .code = "writenop 00020574 2", .unlock = "Sol" },
    { .code = "writenop 00159F94 0", .unlock = "Valve" },
    { .code = "writenop 0005EEB3 2", .unlock = "ParallaxSpriteOOZ" },

    // LRZ1
    { .code = "writenop 0000D308 2", .unlock = "BridgeLRZ1" },
    { .code = "writenop 000866BC 2", .unlock = "ButtonLRZ1" },
    { .code = "writenop 000E8D91 2", .unlock = "ButtonDoorLRZ1" },
    { .code = "writenop 000E1906 2", .unlock = "Drillerdroid" },
    { .code = "writenop 0011357C 2", .unlock = "DrillerdroidO" },
    { .code = "writenop 000E4786 2", .unlock = "FirewormLRZ1" },
    { .code = "writenop 000A3E66 2", .unlock = "IwamodokiLRZ1" },
    { .code = "writenop 00112D11 2", .unlock = "LRZFireball" },
    { .code = "writenop 000DFF39 2", .unlock = "LRZRockPileLRZ1" },
    { .code = "writenop 00112900 2", .unlock = "LavaFall" },
    { .code = "writenop 000DE970 2", .unlock = "LavaGeyserLRZ1" },
    { .code = "writenop 00161627 2", .unlock = "OrbitSpikeLRZ1" },
    { .code = "writenop 00173196 2", .unlock = "RexonLRZ1" },
    { .code = "writenop 00174D46 2", .unlock = "RockDrill" },
    { .code = "writenop 000E1136 2", .unlock = "Stalactite" },
    { .code = "writenop 000E52D6 2", .unlock = "ToxomisterLRZ1" },
    { .code = "writenop 001A1B61 2", .unlock = "WalkerLegsLRZ1" },

    // LRZ2
    { .code = "writenop 00075924 2", .unlock = "FlamethrowerLRZ2" },
    { .code = "writenop 0005EEF4 2", .unlock = "ParallaxSpriteLRZ2" },
    { .code = "writenop 001983F1 2", .unlock = "Turbine" },

    // LRZ3
    { .code = "writenop 0007D900 2", .unlock = "CutsceneHBHHeavyKing" },
    { .code = "writenop 0007D8C0 6", .unlock = "CutsceneHBHHeavyRider" },

    // MMZ
    { .code = "writenop 000DC1E0 2", .unlock = "Bomb" },
    { .code = "writenop 00086641 2", .unlock = "ButtonMMZ" },
    { .code = "writenop 000EC410 2", .unlock = "Caterkiller" },
    { .code = "writenop 000F60A1 2", .unlock = "ConveyorBelt" },
    { .code = "writenop 000F6511 2", .unlock = "ConveyorWheel" },
    { .code = "writenop 00157610 2", .unlock = "MatryoshkaBom" },
    { .code = "writenop 001583A7 2", .unlock = "MechaBu" },
    { .code = "writenop 001604C1 2", .unlock = "OneWayDoorMMZ" },
    { .code = "writenop 00160A10 2", .unlock = "Orbinaut" },
    { .code = "writenop 0016AEB0 2", .unlock = "PohBee" },
    { .code = "writenop 00179360 2", .unlock = "Scarab" },

    // TMZ
    { .code = "writenop 000D81F2 2", .unlock = "BallHog" },
    { .code = "writenop 00086723 2", .unlock = "ButtonTMZ3" },
    { .code = "writenop 00129333 2", .unlock = "FlasherMKII" },
    { .code = "writenop 0001FC82 2", .unlock = "GymBar" },
    { .code = "writenop 00156DC8 2", .unlock = "MagnetSphere" },
    { .code = "writenop 00080455 2", .unlock = "RubyPortalTMZ2" },
    { .code = "writenop 0017B313 2", .unlock = "SentryBug" },
    { .code = "writenop 001926E2 2", .unlock = "TeeterTotter" },
    { .code = "writenop 001A2E92 2", .unlock = "WallBumper" },

    // AIZ
    { .code = "writenop 000D0E64 2", .unlock = "AIZTornado" },
    { .code = "writenop 000DBBC1 2", .unlock = "Bloominator" },
    { .code = "writenop 000ED3A1 2", .unlock = "CaterkillerJrAIZ" },
    { .code = "writenop 00080455 2", .unlock = "RubyPortalAIZ" },
    { .code = "writenop 00173EE1 2", .unlock = "Rhinobot" },
    { .code = "writenop 00190991 2", .unlock = "SweepAIZ" },
    { .code = "writenop 0019192B 2", .unlock = "SwingRopeAIZ" },
    { .code = "writenop 0008ADA3 2", .unlock = "PlatformAIZ" },

    // END
    { .code = "END", .unlock = "END" },
};
// clang-format on

void Trim(char *str)
{
    if (str != NULL && *str != '\0') {
        memmove(str, str + 6, strlen(str));
    }
}

void InitUnlocks(void)
{
    memset(activeUnlocks, 0, sizeof(activeUnlocks));

    unlockedCount = 0;
    
    // WARNING: THIS CODE SUCKS ASS
    // Partially because of how RSDK handles strings, partially because I'm bad at coding

    String id;
    INIT_STRING(id);
    while (Mod.ForeachModID(&id)) {
        // Get mod path
        char cStr[MAX_LEN];
        RSDK.GetCString(cStr, &id);
        String lstPath;
        INIT_STRING(lstPath);
        Mod.GetModPath(&cStr, &lstPath);

        if (!lstPath.length) // Mod is inactive
            continue;

        // Get LST filename
        String iniPath = lstPath;

        String append;
        INIT_STRING(append);
        RSDK.InitString(&append, "/mod.ini", 0);
        RSDK.AppendString(&iniPath, &append);
        RSDK.GetCString(cStr, &iniPath);

        FileIO *file = fOpen(cStr, "r");
        if (file == NULL) // Not sure how a valid mod would be missing a mod.ini file, but just in case
            continue;

        char lstName[MAX_LEN] = "/";

        char buffer[MAX_LEN];
        while (fgets(buffer, MAX_LEN, file)) {
            // Remove trailing newline
            buffer[strcspn(buffer, "\n")] = 0;

            if (strncmp("Codes=", buffer, 6) == 0) { // If this is the Codes flag
                Trim(buffer);
                strcat_s(lstName, MAX_LEN, buffer);
                break;
            }
        }

        fClose(file);

        if (strlen(lstName) == 1) // If the string is simply "/" then no codes list is used in the mod
            continue;

        // Append the name to the mod path
        INIT_STRING(append);
        RSDK.InitString(&append, lstName, 0);
        RSDK.AppendString(&lstPath, &append);
        RSDK.GetCString(cStr, &lstPath);

        // Now actually open the file
        FileIO *file2 = fOpen(cStr, "r");
        if (file2 == NULL) {
            RSDK.PrintLog(PRINT_ERROR, "%s not found", cStr);
            continue;
        }

        while (fGets(buffer, MAX_LEN, file2)) {
            // Remove trailing newline
            buffer[strcspn(buffer, "\n")] = 0;

            // Skip lines that do not begin with "writenop"
            if (strncmp("writenop", buffer, 8) != 0)
                continue;

            for (uint32 i = 0; i < 0x200; i++) {
                if (unlockCodes[i].code == "END") {
                    RSDK.PrintLog(PRINT_ERROR, "Code \"%s\" is not supported", buffer);
                    break;
                }
                else if (strcmp(unlockCodes[i].code, buffer) == 0) {
                    if (!CheckUnlock(unlockCodes[i].unlock)) {
                        strcpy_s(activeUnlocks[unlockedCount], MAX_LEN, unlockCodes[i].unlock);
                        RSDK.PrintLog(PRINT_NORMAL, "%s added to unlock list", unlockCodes[i].unlock);
                        if (++unlockedCount >= UNLOCK_MAX)
                            RSDK.PrintLog(PRINT_NORMAL, "Unlock limit reached!");
                    }
                    else
                        RSDK.PrintLog(PRINT_NORMAL, "%s is already in the unlock list", unlockCodes[i].unlock);
                    break;
                }
            }
            if (unlockedCount >= UNLOCK_MAX)
                break;
        }

        fClose(file2);

        if (unlockedCount >= UNLOCK_MAX)
            break;
    }
}

bool32 CheckUnlock(const char *unlock)
{
    for (int32 i = 0; i < unlockedCount; i++) {
        if (strcmp(activeUnlocks[i], unlock) == 0)
            return true;
    }
    return false;
}
