#include "GameAPI/Game.h"
#include "ModConfig.h"
#include "Player.h"
#include "ContinuePlayer.h"
#include "BSS_Player.h"
#include "HCZSetup.h"
#include "CPZSetup.h"
#include "MenuSetup.h"

ModConfig config;

ObjectHCZSetup *HCZSetup;
ObjectCPZSetup *CPZSetup;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void HCZSetup_StageLoad(void)
{
    RSDK_THIS(HCZSetup);

    Mod.Super(HCZSetup->classID, SUPER_STAGELOAD, NULL);

    // Apply default underwater palette
    // (Technically this could be done in Player_StageLoad, but then the Encore palette would overwrite the palettes)
    for (int32 i = 0; i < PLAYER_PRIMARY_COLOR_COUNT; i++) {
        RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_SONIC + i, Player->superPalette_Sonic_HCZ[i]);
        RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_TAILS + i, Player->superPalette_Tails_HCZ[i]);
        RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_KNUX + i, Player->superPalette_Knux_HCZ[i]);
#if MANIA_USE_PLUS
        RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_MIGHTY + i, Player->superPalette_Mighty_HCZ[i]);
        RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_RAY + i, Player->superPalette_Ray_HCZ[i]);
#endif
    }
}

void CPZSetup_StageLoad(void)
{
    RSDK_THIS(CPZSetup);

    Mod.Super(CPZSetup->classID, SUPER_STAGELOAD, NULL);

    // Apply default underwater palette
    // (Technically this could be done in Player_StageLoad, but then the Encore palette would overwrite the palettes)
    for (int32 i = 0; i < PLAYER_PRIMARY_COLOR_COUNT; i++) {
        RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_SONIC + i, Player->superPalette_Sonic_CPZ[i]);
        RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_TAILS + i, Player->superPalette_Tails_CPZ[i]);
        RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_KNUX + i, Player->superPalette_Knux_CPZ[i]);
#if MANIA_USE_PLUS
        RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_MIGHTY + i, Player->superPalette_Mighty_CPZ[i]);
        RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_RAY + i, Player->superPalette_Ray_CPZ[i]);
#endif
    }
}

void InitModAPI(void)
{
    // Setup Config
    config.allowSamePalettes = Mod.GetSettingsBool("", "Config:allowSamePalettes", false);
    Mod.SetSettingsBool("Config:allowSamePalettes", config.allowSamePalettes);
    Mod.SaveSettings();

    ADD_PUBLIC_FUNC(Player_RandomizePalettes);
    ADD_PUBLIC_FUNC(Player_SetPalette);
    ADD_PUBLIC_FUNC(Player_GetPalettes);

    MOD_REGISTER_OBJ_OVERLOAD(Player, NULL, NULL, NULL, NULL, NULL, Player_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(ContinuePlayer, NULL, NULL, NULL, NULL, NULL, ContinuePlayer_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(BSS_Player, NULL, NULL, NULL, NULL, NULL, BSS_Player_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(HCZSetup, NULL, NULL, NULL, NULL, NULL, HCZSetup_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(CPZSetup, NULL, NULL, NULL, NULL, NULL, CPZSetup_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(MenuSetup, NULL, NULL, NULL, NULL, NULL, MenuSetup_StageLoad, NULL, NULL, NULL);
}

#if RETRO_USE_MOD_LOADER
void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif
