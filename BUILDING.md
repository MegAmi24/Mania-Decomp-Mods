# Building RSDKv5(U) Decompilation Mods

Mods require the [GameAPI](https://github.com/Rubberduckycooly/GameAPI) dependency to build. To set it up, simply clone the repo in a folder named `GameAPI` in the mod's root directory.
If you plan to build multiple mods, using symlinks is recommended.

## Building in Visual Studio
Simply open the solution and build the project. Make sure that the architecture, engine revision, game version, and mod loader version match with the target engine and game decompilation binaries.

## Setting Up SymLink for Android
To add a symbolic link for your mod, write the appropriate command in `[RSDKv5-decompilation-root]/android/app/jni`:
  * Windows: `mklink /d "[mod-folder-name]" "[path-to-mod-root]"`
  * Linux: `ln -s "[path-to-mod-root]" "[mod-folder-name]"`

After adding the symlink(s), build the decompilation in Android Studio.