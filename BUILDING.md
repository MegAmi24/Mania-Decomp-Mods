# Building RSDKv5(U) Decompilation Mods

> [!WARNING]
> The building process for some mods may vary due to various factors, from folder structure to external dependencies. This guide is made for the mods in this repository, and while I tried my best to cover what to do in other scenarios, I can only do so much.

## Get the source code
First, you will need to clone the repository containing the source code for the mod. To do this, you need to install Git, which you can find [here](https://git-scm.com/downloads).

Clone the repo **recursively**, using:
`git clone [link-to-github-repository] --recursive`

If you've already cloned the repo, run these commands inside of the repository to ensure the clone is up-to-date:
```
git pull
git submodule update --remote --init --recursive
```

## Set up GameAPI
Mods require the [GameAPI](https://github.com/RSDKModding/RSDKv5-GameAPI) dependency to build.
Some repositories (such as this one) include GameAPI as a submodule, which is downloaded along with the repository when cloned recursively. Others don't include it, in which case you can simply clone it by running `git clone https://github.com/RSDKModding/RSDKv5-GameAPI --recursive` (if you plan to build multiple mods, using symlinks is recommended). When doing this, keep in mind that the location GameAPI needs to be in may differ from repo to repo; most will have it in the mod's root directory, but others may have it elsewhere. If you're getting errors with GameAPI not being found despite cloning the repo in the correct location, you may need to rename the `RSDKv5-GameAPI` folder to `GameAPI`.

## Building

### Building with CMake
Besides GameAPI, no external dependencies are required; simply type the following commands in the mod's root directory:
```
cmake -B build
cmake --build build --config release
```

The resulting build will be located somewhere in `build/` depending on your system.

The following CMake arguments are available when compiling (only use these if you know what you're doing!):
- Use these by adding `-D[flag-name]=[value]` to the end of the `cmake -B build` command. For example, to build with `RETRO_REVISION` set to 2, add `-DRETRO_REVISION=2` to the command.

#### GameAPI Mod flags
- `RETRO_REVISION`: What RSDKv5 revision to compile for. Takes an integer, defaults to `3` (RSDKv5U).
- `RETRO_MOD_LOADER_VER`: Manually sets the mod loader version. Takes an integer, defaults to the current latest version.
- `MANIA_FIRST_RELEASE`: Whether or not to build the first release of Sonic Mania. Takes a boolean, defaults to `off`.
- `MANIA_PRE_PLUS`: Whether or not to build a pre-plus version of Sonic Mania. Takes a boolean, defaults to `off`.
- `GAME_VERSION`: Which release version of Sonic Mania to target for. Takes an integer, defaults to `3` when `MANIA_PRE_PLUS` is enabled, and `6` otherwise (last Steam release).
- `MOD_INCLUDE_EDITOR`: Whether or not to include functions for use in certain RSDKv5 scene editors. For mods, this generally doesn't matter. Takes a boolean, defaults to `on`.

### Building in Visual Studio
Simply open the solution and build the project. Make sure that the architecture, engine revision, game version, and mod loader version match with the target engine and game decompilation binaries.

### Building for Android
After [setting up the RSDKv5(U) decompilation for building](https://github.com/Rubberduckycooly/RSDKv5-Decompilation#how-to-build), you will need to add a symbolic link for the root directory of the mod so that it will be built as part of the APK. The root directory of the mod is the folder in the repository containing the `CMakeLists.txt` file. To add the symlink, write the appropriate command in `[RSDKv5-decompilation-root]/android/app/jni`:
  * Windows: `mklink /d "[mod-logicfile-name]" "[path-to-mod-root]"`
  * Linux: `ln -s "[path-to-mod-root]" "[mod-logicfile-name]"`

It's important that `[mod-logicfile-name]` matches the name given for the `LogicFile` tag in the mod's `mod.ini` file.

After adding the symlinks, build the decompilation in Android Studio. Don't forget to add the `mod.ini` file and `Data` folder (if there is one) for the mod to a folder in your setup's `mods` folder!
