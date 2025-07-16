import os, re

def main():
    filenames = []
    overloads = []
    unfinished = []
    unlocks = set()

    print("Reading Objects folder...")

    for dir_, _, files in os.walk("Objects"):
        for file_name in files:
            rel_dir = os.path.relpath(dir_, "Objects")
            if file_name.endswith(".c"):
                try:
                    add_unlocks = False
                    with open(os.path.join(dir_, file_name[:-1] + 'h'), "r") as f:
                        content = f.read()
                        if "_Serialize(void);" not in content:
                            filenames.append(f"{rel_dir}/{file_name}")
                            add_unlocks = True
                    if add_unlocks == True:
                        with open(os.path.join(dir_, file_name), "r") as f:
                            content = f.read()
                            fileunlocks = [u[13:-2] for u in re.findall(r"CheckUnlock\(\".*?\"\)", content)]
                            unlocks.update(fileunlocks)
                except FileNotFoundError:
                    print(f"{os.path.join(dir_, file_name[:-1] + 'h')} not found")
                except Exception as e:
                    print(f"ERROR: {e}")
            elif file_name.endswith(".h") and file_name != "All.h":
                with open(os.path.join(dir_, file_name), "r") as f:
                    content = f.read()
                    if "_Serialize(void);" not in content:
                        filenames.append(f"{rel_dir}/{file_name}")

                        update = f"{file_name[:-2]}_Update" if "_Update(void);" in content else "NULL"
                        lateupdate = f"{file_name[:-2]}_LateUpdate" if "_LateUpdate(void);" in content else "NULL"
                        staticupdate = f"{file_name[:-2]}_StaticUpdate" if "_StaticUpdate(void);" in content else "NULL"
                        draw = f"{file_name[:-2]}_Draw" if "_Draw(void);" in content else "NULL"
                        create = f"{file_name[:-2]}_Create" if "_Create(void *data);" in content else "NULL"
                        stageload = f"{file_name[:-2]}_StageLoad" if "_StageLoad(void);" in content else "NULL"

                        overloads.append(f"    MOD_REGISTER_OBJ_OVERLOAD({file_name[:-2]}, {update}, {lateupdate}, {staticupdate}, {draw}, {create}, {stageload}, NULL, NULL, NULL);\n")
                    else:
                        unfinished.append(f"{rel_dir}/{file_name[:-2]}\n")

    print("Writing Objects.cmake...")
    filescmake = ["\t${MOD_NAME}/Objects/" + f + "\n" for f in filenames if f.endswith(".c")]
    with open("Objects.cmake", "w") as f:
        f.writelines(["# This file is auto-generated, do not edit it\n\nset(GENERATED_SOURCES\n"] + filescmake + [")\n"])

    print("Writing Objects/All.h...")
    filesheader = ['#include "' + f + '"\n' for f in filenames if f.endswith(".h") and not f.endswith("All.h")]
    with open("Objects/All.h", "w") as f:
        f.writelines(["// This file is auto-generated, do not edit it\n\n"] + filesheader)

    print("Writing Overloads.h...")
    with open("Overloads.h", "w") as f:
        f.writelines(['#ifndef OVERLOADS_H\n#define OVERLOADS_H\n\n// This file is auto-generated, do not edit it\n\n#include "GameAPI/Game.h"\n#include "Objects/All.h"\n\nvoid RegisterOverloads(void) {\n'] + overloads + ["}\n\n#endif //! OVERLOADS_H\n"])

    print("Checking unlocks...\n")
    unused = set()
    nonexistant = set()

    with open("UnlockCodes.c", "r") as f:
        content = f.read()
        allunlocks = [u[11:-1] for u in re.findall(r"\.unlock = \".*?\"", content)]
        for unlock in allunlocks:
            if unlock not in unlocks and unlock != "END":
                unused.add(unlock + "\n")
        for unlock in unlocks:
            if unlock not in allunlocks:
                nonexistant.add(unlock + "\n")

    if len(unused) > 0:
        print("[WARNING] The following unlocks are unused:\n", *unused)
    if len(nonexistant) > 0:
        print("[WARNING] The following unlocks do not exist:\n", *nonexistant)
    if len(unfinished) > 0:
        print("[WARNING] The following objects are not finished:\n", *unfinished)

    print("Done!")
    os.system('pause')

if __name__ == '__main__':
    main()
