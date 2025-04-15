#include "GameAPI/Game.h"
#include "MenuSetup.h"
#include "Player.h"
#include "ModConfig.h"

ObjectMenuSetup *MenuSetup;

void MenuSetup_StageLoad(void)
{
    RSDK_THIS(MenuSetup);

    Mod.Super(MenuSetup->classID, SUPER_STAGELOAD, NULL);

    LoadPlayerPalettes();

    int32 charPalettes[PLAYER_CHARACTER_COUNT];

    for (int32 c = 0; c < PLAYER_CHARACTER_COUNT; c++) {
        int32 pal = 0, bank = 0;

        if (config.allowSamePalettes || c == 0) {
            RandomPalette(pal, bank);
        }
        else {
            charPalettes[c] = -1;
            while (charPalettes[c] == -1) {
                int32 newPal = RSDK.Rand(0, PLAYER_PALETTE_COUNT);

                // Check the characters we've set before this to make sure the new color wasn't used already
                int32 i = 0;
                for (; i < c; i++) {
                    if (charPalettes[i] == newPal)
                        break;
                }

                // If we've made it to the current character, then this is a new palette
                if (i == c)
                    charPalettes[c] = newPal;
            }
            SetPalette(charPalettes[c], pal, bank);
        }

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
