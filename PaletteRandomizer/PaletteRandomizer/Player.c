#include "GameAPI/Game.h"
#include "Player.h"
#include "ModConfig.h"

ObjectPlayer *Player;

void Player_StageLoad(void)
{
    RSDK_THIS(Player);

    Mod.Super(Player->classID, SUPER_STAGELOAD, NULL);

    LoadPlayerPalettes();

    int32 charPalettes[PLAYER_CHARACTER_COUNT];

    Player_GetPalettes(charPalettes);

    for (int32 c = 0; c < PLAYER_CHARACTER_COUNT; c++) {
        int32 pal = 0, bank = 0;

        Player_SetPalette(charPalettes[c], &pal, &bank);

        switch (c) {
            case 0: // Sonic
                for (int32 i = 0; i < PLAYER_PRIMARY_COLOR_COUNT; i++) {
                    Player->superPalette_Sonic[i]                                    = RSDK.GetPaletteEntry(bank, pal + i);
                    Player->superPalette_Sonic[i + PLAYER_PRIMARY_COLOR_COUNT]       = RSDK.GetPaletteEntry(bank, pal + i + PLAYER_PRIMARY_COLOR_COUNT);
                    Player->superPalette_Sonic[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] = RSDK.GetPaletteEntry(bank, pal + i);

                    Player->superPalette_Sonic_HCZ[i] = RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 2));
                    Player->superPalette_Sonic_HCZ[i + PLAYER_PRIMARY_COLOR_COUNT] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 3));
                    Player->superPalette_Sonic_HCZ[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 2));

                    Player->superPalette_Sonic_CPZ[i] = RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 4));
                    Player->superPalette_Sonic_CPZ[i + PLAYER_PRIMARY_COLOR_COUNT] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 5));
                    Player->superPalette_Sonic_CPZ[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 4));

                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_SONIC + i, Player->superPalette_Sonic[i]);
                }
                break;
            case 1: // Tails
                for (int32 i = 0; i < PLAYER_PRIMARY_COLOR_COUNT; i++) {
                    Player->superPalette_Tails[i]                                    = RSDK.GetPaletteEntry(bank, pal + i);
                    Player->superPalette_Tails[i + PLAYER_PRIMARY_COLOR_COUNT]       = RSDK.GetPaletteEntry(bank, pal + i + PLAYER_PRIMARY_COLOR_COUNT);
                    Player->superPalette_Tails[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] = RSDK.GetPaletteEntry(bank, pal + i + PLAYER_PRIMARY_COLOR_COUNT);

                    Player->superPalette_Tails_HCZ[i] = RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 2));
                    Player->superPalette_Tails_HCZ[i + PLAYER_PRIMARY_COLOR_COUNT] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 3));
                    Player->superPalette_Tails_HCZ[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 3));

                    Player->superPalette_Tails_CPZ[i] = RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 4));
                    Player->superPalette_Tails_CPZ[i + PLAYER_PRIMARY_COLOR_COUNT] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 5));
                    Player->superPalette_Tails_CPZ[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 5));

                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_TAILS + i, Player->superPalette_Tails[i]);
                }
                break;
            case 2: // Knuckles
                for (int32 i = 0; i < PLAYER_PRIMARY_COLOR_COUNT; i++) {
                    Player->superPalette_Knux[i]                                    = RSDK.GetPaletteEntry(bank, pal + i);
                    Player->superPalette_Knux[i + PLAYER_PRIMARY_COLOR_COUNT]       = RSDK.GetPaletteEntry(bank, pal + i + PLAYER_PRIMARY_COLOR_COUNT);
                    Player->superPalette_Knux[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] = RSDK.GetPaletteEntry(bank, pal + i + PLAYER_PRIMARY_COLOR_COUNT);

                    Player->superPalette_Knux_HCZ[i] = RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 2));
                    Player->superPalette_Knux_HCZ[i + PLAYER_PRIMARY_COLOR_COUNT] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 3));
                    Player->superPalette_Knux_HCZ[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 3));

                    Player->superPalette_Knux_CPZ[i] = RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 4));
                    Player->superPalette_Knux_CPZ[i + PLAYER_PRIMARY_COLOR_COUNT] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 5));
                    Player->superPalette_Knux_CPZ[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 5));

                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_KNUX + i, Player->superPalette_Knux[i]);
                }
                break;
#if MANIA_USE_PLUS
            case 3: // Mighty
                for (int32 i = 0; i < PLAYER_PRIMARY_COLOR_COUNT; i++) {
                    Player->superPalette_Mighty[i]                                    = RSDK.GetPaletteEntry(bank, pal + i);
                    Player->superPalette_Mighty[i + PLAYER_PRIMARY_COLOR_COUNT]       = RSDK.GetPaletteEntry(bank, pal + i + PLAYER_PRIMARY_COLOR_COUNT);
                    Player->superPalette_Mighty[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] = RSDK.GetPaletteEntry(bank, pal + i + PLAYER_PRIMARY_COLOR_COUNT);

                    Player->superPalette_Mighty_HCZ[i] = RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 2));
                    Player->superPalette_Mighty_HCZ[i + PLAYER_PRIMARY_COLOR_COUNT] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 3));
                    Player->superPalette_Mighty_HCZ[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 3));

                    Player->superPalette_Mighty_CPZ[i] = RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 4));
                    Player->superPalette_Mighty_CPZ[i + PLAYER_PRIMARY_COLOR_COUNT] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 5));
                    Player->superPalette_Mighty_CPZ[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 5));

                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_MIGHTY + i, Player->superPalette_Mighty[i]);
                }
                break;
            case 4: // Ray
                for (int32 i = 0; i < PLAYER_PRIMARY_COLOR_COUNT; i++) {
                    Player->superPalette_Ray[i]                                    = RSDK.GetPaletteEntry(bank, pal + i);
                    Player->superPalette_Ray[i + PLAYER_PRIMARY_COLOR_COUNT]       = RSDK.GetPaletteEntry(bank, pal + i + PLAYER_PRIMARY_COLOR_COUNT);
                    Player->superPalette_Ray[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] = RSDK.GetPaletteEntry(bank, pal + i + PLAYER_PRIMARY_COLOR_COUNT);

                    Player->superPalette_Ray_HCZ[i] = RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 2));
                    Player->superPalette_Ray_HCZ[i + PLAYER_PRIMARY_COLOR_COUNT] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 3));
                    Player->superPalette_Ray_HCZ[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 3));

                    Player->superPalette_Ray_CPZ[i] = RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 4));
                    Player->superPalette_Ray_CPZ[i + PLAYER_PRIMARY_COLOR_COUNT] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 5));
                    Player->superPalette_Ray_CPZ[i + (PLAYER_PRIMARY_COLOR_COUNT * 2)] =
                        RSDK.GetPaletteEntry(bank, pal + i + (PLAYER_PRIMARY_COLOR_COUNT * 5));

                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_RAY + i, Player->superPalette_Ray[i]);
                }
                break;
#endif
        }
    }

    RestorePalettes();
}

void Player_RandomizePalettes(void)
{
    LoadPlayerPalettes();

    int32 charPalettes[PLAYER_CHARACTER_COUNT];

    Player_GetPalettes(charPalettes);

    for (int32 c = 0; c < PLAYER_CHARACTER_COUNT; c++) {
        int32 pal = 0, bank = 0;

        Player_SetPalette(charPalettes[c], &pal, &bank);

        int32 index;
        switch (c) {
            case 0: index = PLAYER_PALETTE_INDEX_SONIC; break;
            case 1: index = PLAYER_PALETTE_INDEX_TAILS; break;
            case 2: index = PLAYER_PALETTE_INDEX_KNUX; break;
#if MANIA_USE_PLUS
            case 3: index = PLAYER_PALETTE_INDEX_MIGHTY; break;
            case 4: index = PLAYER_PALETTE_INDEX_RAY; break;
#endif
        }

        for (int32 i = 0; i < PLAYER_PRIMARY_COLOR_COUNT; i++) RSDK.SetPaletteEntry(0, index + i, RSDK.GetPaletteEntry(bank, pal + i));
    }

    RestorePalettes();
}

void Player_SetPalette(int32 id, int32 *pal, int32 *bank)
{
    if (pal && bank) {
        *pal = id;

        *bank = PLAYER_PALETTE_BANK_START;
        while (*pal >= 7) {
            *pal -= 7;
            if (*bank < PALETTE_BANK_COUNT - 1)
                *bank += 1;
        }

        *pal *= (PLAYER_PRIMARY_COLOR_COUNT * 6);
    }
}

void Player_GetPalettes(int32 *palTable)
{
    for (int32 c = 0; c < PLAYER_CHARACTER_COUNT; c++) {
        if (config.allowSamePalettes || c == 0 || c >= PLAYER_PALETTE_COUNT)
            palTable[c] = RSDK.Rand(0, PLAYER_PALETTE_COUNT);
        else {
            palTable[c] = -1;
            while (palTable[c] == -1) {
                int32 newPal = RSDK.Rand(0, PLAYER_PALETTE_COUNT);

                // Check the characters we've set before this to make sure the new color wasn't used already
                int32 i = 0;
                for (; i < c; i++) {
                    if (palTable[i] == newPal)
                        break;
                }

                // If we've made it to the current character, then this is a new palette
                if (i == c)
                    palTable[c] = newPal;
            }
        }
    }
}
