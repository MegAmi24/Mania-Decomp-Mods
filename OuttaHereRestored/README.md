# Outta Here Restored
Makes Sonic's "I'm outta here!" easter egg trigger as it did in Sonic CD, with some additional features.

[GameBanana Page](https://gamebanana.com/mods/398209)

## Mod Settings Info
* ``[character]CanOuttaHere`` - Determines if the character can activate the Outta Here sequence.
* ``sidekickCanOuttaHere`` - 0 = Sidekick can't Outta Here, 1 = Sidekick uses the animation set in `[character]AnimID` for the appropriate character, 2 = Sidekick uses the animation set in `sidekickAnimID`. `[character]CanOuttaHere` settings still apply.
* ``[character]AnimID`` - Specifies which animation ID to use for each character when not a sidekick. Setting this to -1 will use the appropriate character's animation from `Players/OuttaHere.bin` instead of the one from the character's animation file.
  * For compatibility with mods that used Rubberduckycooly's [Outta Here Returns](https://gamebanana.com/mods/48028) mod, set this to the ID that the original mod specifies (this will usually be 27).
* ``sidekickAnimID`` - Specifies which animation ID to use for the sidekick when `sidekickCanOuttaHere` is set to 2. The -1 setting works here too.
* ``useFrameID`` - When enabled, the jump will occur on the frame of the animation with its "ID" set to anything except for 0. Otherwise, the jump will always occur on frame 14.
* ``useVoiceLines`` - 0 = Disable sound effect, 1 = Use Sonic's "I'm outta here!" line for all characters, 2 = Unique sound effect for each character.
