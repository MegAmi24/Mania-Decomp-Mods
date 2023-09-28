# Building RSDKv5(U) Decompilation Mods
It should be noted that the building process for some mods may vary due to various factors, from folder structure to external dependencies. This guide is made for the mods in this repository, although it should work with a majority of other ones.

## Get the source code
First, you will need to clone the repository containing the source code for the mod. To do this, you need to install Git, which you can find [here](https://git-scm.com/downloads).

Clone the repo **recursively**, using:
`git clone [link-to-github-repository] --recursive`

If you've already cloned the repo, run this command inside of the repository:
```git submodule update --init```

## Set up GameAPI
Mods require the [GameAPI](https://github.com/Rubberduckycooly/GameAPI) dependency to build.
Some repositories (such as this one) include GameAPI as a submodule, which is downloaded along with the repository when cloned with the above command. Others don't include it, in which case you can simply clone it by running `git clone https://github.com/Rubberduckycooly/GameAPI --recursive` (if you plan to build multiple mods, using symlinks is recommended). When doing this, keep in mind that the location GameAPI needs to be in may differ from repo to repo; most will have it in the mod's root directory, but others may have it elsewhere.

## Building

### Building with CMake
Besides GameAPI, no external dependencies are required; simply type the following commands in the mod's root directory:
```
cmake -B build
cmake --build build --config release
```

The resulting build will be located somewhere in `build/` depending on your system.

The following cmake arguments are available when compiling:
- Use these on the `cmake -B build` step like so: `cmake -B build -DRETRO_REVISION=2`

#### GameAPI Mod flags
- `RETRO_REVISION`: What RSDKv5 revision to compile for. Takes an integer, defaults to `3` (RSDKv5U).
- `RETRO_MOD_LOADER_VER`: Manually sets the mod loader version. Takes an integer, defaults to the current latest version.
- `MANIA_FIRST_RELEASE`: Whether or not to build the first release of Sonic Mania. Takes a boolean, defaults to `off`.
- `MANIA_PRE_PLUS`: Whether or not to build a pre-plus version of Sonic Mania. Takes a boolean, defaults to `off`.
- `GAME_VERSION`: Which release version of Sonic Mania to target for. Takes an integer, defaults to `3` when `MANIA_PRE_PLUS` is enabled, and `6` otherwise (last steam release).
- `MOD_INCLUDE_EDITOR`: Whether or not to include functions for use in certain RSDKv5 scene editors. For mods, this generally doesn't matter. Takes a boolean, defaults to `on`.

### Building in Visual Studio
Simply open the solution and build the project. Make sure that the architecture, engine revision, game version, and mod loader version match with the target engine and game decompilation binaries.

### Setting Up SymLink for Android
To add a symbolic link for your mod, write the appropriate command in `[RSDKv5-decompilation-root]/android/app/jni`:
  * Windows: `mklink /d "[mod-folder-name]" "[path-to-mod-root]"`
  * Linux: `ln -s "[path-to-mod-root]" "[mod-folder-name]"`

After adding the symlink(s), build the decompilation in Android Studio.