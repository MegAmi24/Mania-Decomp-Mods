import os

for dir_, _, files in os.walk("Objects"):
    for file_name in files:
        rel_dir = os.path.relpath(dir_, "Objects")
        if file_name.endswith(".c"):
            old_c_header = f'// ---------------------------------------------------------------------\n// RSDK Project: Sonic Mania\n// Object Description: {file_name[:-2]} Object\n// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges\n// Decompiled by: Rubberduckycooly & RMGRich\n// ---------------------------------------------------------------------\n\n#include "Game.h"'
            new_c_header = f'#include "GameAPI/Game.h"\n#include "UnlockCodes.h"\n#include "{file_name[:-1]}h"'
            try:
                with open(os.path.join(dir_, file_name), "r+") as f:
                    content = f.read().replace(old_c_header, new_c_header)
                    f.seek(0)
                    f.write(content)
                    f.truncate()
            except Exception as e:
                print(f"An unexpected error occurred: {e}")
