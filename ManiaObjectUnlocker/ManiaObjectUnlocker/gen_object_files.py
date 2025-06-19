import os
import re

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
                with open(os.path.join(dir_, file_name[:-1] + 'h'), "r") as f:
                    content = f.read()
                    if "_Serialize(void);" not in content:
                        filenames.append(f"{rel_dir}/{file_name}")
                with open(os.path.join(dir_, file_name), "r") as f:
                    content = f.read()
                    fileunlocks = [u[13:-2] for u in re.findall(r"CheckUnlock\(\".*\"\)", content)]
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
                    if "_Create(void *data);" in content and "_StageLoad(void);" in content:
                        overloads.append("    ADD_OVERLOAD_CREATE_STAGELOAD(" + file_name[:-2] + ");\n")
                    elif "_Create(void *data);" in content:
                        overloads.append("    ADD_OVERLOAD_CREATE(" + file_name[:-2] + ");\n")
                    else:
                        overloads.append("    ADD_OVERLOAD_STAGELOAD(" + file_name[:-2] + ");\n")
                else:
                    unfinished.append(f"{rel_dir}/{file_name[:-2]}\n")


print("Writing Objects.cmake...")
filescmake = ["\t${MOD_NAME}/Objects/" + f + "\n" for f in filenames if f.endswith(".c")]
with open("Objects.cmake", "w") as f:
    f.writelines(["set(GENERATED_SOURCES\n"] + filescmake + [")\n"])

print("Writing Objects/All.h...")
filesheader = ["#include \"" + f + "\"\n" for f in filenames if f.endswith(".h") and not f.endswith("All.h")]
with open("Objects/All.h", "w") as f:
    f.writelines(filesheader)

print("Writing Overloads.h...")
with open("Overloads.h", "w") as f:
    f.writelines(["#include \"Objects/All.h\"\n\n#define ADD_OVERLOAD_CREATE(object)           MOD_REGISTER_OBJ_OVERLOAD(object, NULL, NULL, NULL, NULL, object##_Create, NULL, NULL, NULL, NULL)\n#define ADD_OVERLOAD_STAGELOAD(object)        MOD_REGISTER_OBJ_OVERLOAD(object, NULL, NULL, NULL, NULL, NULL, object##_StageLoad, NULL, NULL, NULL)\n#define ADD_OVERLOAD_CREATE_STAGELOAD(object) MOD_REGISTER_OBJ_OVERLOAD(object, NULL, NULL, NULL, NULL, object##_Create, object##_StageLoad, NULL, NULL, NULL)\n\nvoid RegisterOverloads(void) {\n"] + overloads + ["}"])

print("Checking unlocks...")
unused = set()
nonexistant = set()

print("")

with open("UnlockCodes.c", "r") as f:
    content = f.read()
    allunlocks = [u[11:-1] for u in re.findall(r"\.unlock = \".*\"", content)]
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