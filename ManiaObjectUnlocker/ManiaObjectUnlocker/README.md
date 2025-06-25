# Helper Scripts

## gen_object_files.py

Running this script will:

- Update `Objects/All.h` to include all object header files in the `Objects` folder, sans `All.h` itself
- Update `Objects.cmake` to include all object code files in the `Objects` folder
- Update `Overloads.h` to add object overload registers for all objects. The script will read the objects' header files to detect which events have overload functions.
- Check the unlock names given to all uses of the `CheckUnlock` function in the object code with the list of unlocks in `UnlockCodes.c` and display warnings for unlock names present in the unlock list but not in the object code (unused unlocks) or vice versa (non-existant unlocks)

If an object's header file includes a Serialize function in it, the object will be declared "unfinished" and will not be included in any file updates or checks. A list of unfinished objects will be displayed when running this script, if any are present.

## init_object_headers.py

Running this script will replace any instances of the default Sonic Mania Decompilation headers and include in all object code files with the necessary includes for the mod and the object.
