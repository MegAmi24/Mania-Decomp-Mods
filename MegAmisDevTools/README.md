# MegAmi's Dev Tools
Adds a debug menu with several features

## Features
* Adds a debug menu accessed by pressing Select (mapped to Tab on keyboard by default) while in-game. Allows:
  * Changing current character, sidekick, encore stocks, and shield
  * Activating speed shoes
  * Toggling Hyper Ring
  * Manually setting ring count
  * (De)activating Super form
  * Toggling invincibility
* Debug Mode automatically gets enabled on scene load
* Debug Mode no longer disables act/zone transitions
* Disables autosave popup message
* Vape Move variable can be toggled without Dev platform
* Default character set on game startup can be changed via mod settings (see [Mod Settings Info](#mod-settings-info))

## Mod Settings Info
* ``defaultLeader`` - ID of leader character set on startup. Minimum 0 (Sonic), Maximum is either 2 (Knuckles) or 4 (Ray) depending on if the Plus DLC is enabled.
* ``defaultSidekick`` - ID of sidekick character set on startup. Minimum -1 (None), Maximum is either 2 (Knuckles) or 4 (Ray) depending on if the Plus DLC is enabled.
