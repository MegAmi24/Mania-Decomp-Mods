import os

for dir_, _, files in os.walk("Objects"):
    for file_name in files:
        rel_dir = os.path.relpath(dir_, "Objects")
        if file_name.endswith(".c"):
            old_c_header = f"// ---------------------------------------------------------------------\n// RSDK Project: Sonic Mania\n// Object Description: {file_name[:-2]} Object\n// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges\n// Decompiled by: Rubberduckycooly & RMGRich\n// ---------------------------------------------------------------------\n\n#include \"Game.h\""
            new_c_header = f"#include \"GameAPI/Game.h\"\n#include \"UnlockCodes.h\"\n#include \"{file_name[:-1]}h\""
            try:
                replace_headers = False
                with open(os.path.join(dir_, file_name[:-1] + 'h'), "r") as f:
                    content = f.read()
                    if "_Serialize(void);" in content:
                        replace_headers = True
                if replace_headers == True:
                    with open(os.path.join(dir_, file_name), "r+") as f:
                        content = f.read().replace(old_c_header, new_c_header)
                        f.seek(0)
                        f.write(content)
                        f.truncate()
            except FileNotFoundError:
                print(f"{os.path.join(dir_, file_name[:-1] + 'h')} not found")
            except Exception as e:
                # This is a general exception handler for any other unexpected errors
                print(f"An unexpected error occurred: {e}")