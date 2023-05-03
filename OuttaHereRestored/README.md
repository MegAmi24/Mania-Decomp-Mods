# Outta Here Restored
Makes Sonic's "I'm outta here!" easter egg trigger as it did in Sonic CD

## Mod Settings Info
* ``[character]CanOuttaHere`` - Determines if the character can activate the Outta Here sequence.
* ``sidekickCanOuttaHere`` - 0 = Sidekick can't Outta Here, 1 = Sidekick uses the regular animation for their character, 2 = Sidekick uses the animation set in `sidekickAnimID`. `[character]CanOuttaHere` settings still apply.
* ``[character]AnimID`` - Specifies which animation ID to use for each character when not a sidekick. This is ignored if `useBinAnim` is enabled.
* ``sidekickAnimID`` - Specifies which animation ID to use for the sidekick when `sidekickCanOuttaHere` is set to 2. This is ignored if `useBinAnim` is enabled.
* ``useBinAnim`` - When enabled, use the appropriate animation from `Players/OuttaHere.bin` instead of the one from the character's animation file. Disable this for compatibility with mods that used the [Outta Here Returns](https://gamebanana.com/mods/48028) mod.
* ``useFrameID`` - When enabled, the jump will occur on the frame of the animation with its "ID" set to anything except for 0. Otherwise, the jump will always occur on frame 14.
* ``useVoiceLines`` - 0 = Disable sound effect, 1 = Use Sonic's "I'm outta here!" line for all characters, 2 = Unique sound effect for each character.

[GameBanana Page](https://gamebanana.com/mods/398209)