# MegAmi's Dev Tools
Adds a debug menu with several features

## Features
* Added Debug menu accessed by pressing Select (mapped to Tab on keyboard by default) while in-game. Allows:
  * Changing current character, sidekick, and shield
  * Activating speed shoes
  * Toggling Hyper Ring
  * Manually setting ring count
  * (De)activating Super form
  * Toggling invincibility
* Debug Mode enabled on scene load
* Debug Mode no longer disables act/zone transitions
* Disabled autosave popup message
* Vape Move variable togglable without Dev platform

## Mod Settings Info
* ``defaultLeader`` - ID of leader character set on startup. Minimum 0 (Sonic), Maximum is either 2 (Knuckles) or 4 (Ray) depending on if the Plus DLC is enabled.
* ``defaultSidekick`` - ID of sidekick character set on startup. Minimum -1 (None), Maximum is either 2 (Knuckles) or 4 (Ray) depending on if the Plus DLC is enabled.
