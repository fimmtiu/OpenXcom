# TO DO

##  Control

How can I script it from the command line? Need command-line options:
* run a battle (-runBattle path_to_battle.cfg) [DONE]
* exit the process when the battle is over (part of -runBattle behaviour) [DONE]
* set a random seed (-randomSeed seed-int) [DONE]
* max number of turns after which the battle is declared over (-maxTurns 50) [DONE]
* file containing the Janet code which JanetAIModule will read (-aiCode path_to_janet_file) [DONE]
* Disable the "Soldier is unconscious" dialog box in battle if -runBattle is present

C++ <-> Janet interface. Need Janet wrappers for the following C++ classes:
* BattleUnit
* ??? FIXME

Global Janet functions to install on startup:

* (visible-units) -- list of all BattleUnits
* (visible-enemies) -- list of all visible enemy BattleUnits
* (visible-friends) -- list of all visible friendly BattleUnits
* (enemy-unit? unit) -- true or false
* (have-grenade?) -- have I used my grenade already?
* (location-of unit) -- returns (x, y, z) list of unit location
* (time-units-remaining) -- integer, time units remaining for self
* (direction-to unit) -- integer (0, 1, 2, 3) indicating direction to the given unit
* (distance-to unit) -- float, distance to unit
* (x-coord unit) -- int, X-coordinate of unit
* (y-coord unit) -- int, Y-coordinate of unit
* (z-coord unit) -- int, Z-coordinate of unit
* (
* (turn) -- what turn is it?
* (health-percentage unit) -- float, returns the health of the given unit from 0% to 100%
  * This means that we let units see the health of enemies. Seems reasonable.
    In practice it will probably just come down to "is this wounded or not?"
FIXME probably lots more.

These immediately exit the function and return a BattleAction struct for the appropriate action.

* (action-walk-to-space x y z) -- move to the given location, or as close to it as we can contrive (Z-coord will be a problem)
* (action-walk-to-unit unit) -- move as close to the given unit as possible
* (action-snap-shot unit) -- snap shot at the given unit
* (action-snap-shot-at x y z) -- snap shot at the given location, ignoring anything in the way
* (action-auto-shot unit) -- auto shot at the given unit
* (action-auto-shot-at x y z) -- auto shot at the given location, ignoring anything in the way
* (action-aimed-shot unit) -- aimed shot at the given unit
* (action-aimed-shot-at x y z) -- aimed shot at the given location, ignoring anything in the way
* (action-prime-grenade) -- prime a grenade, or do nothing if there is no grenade or it is already primed.
* (action-throw-grenade unit) -- throw grenade at the given unit, or do nothing if we don't have one.
* (action-throw-grenade-at x y z) -- throw grenade at the given location, ignoring anything in the way, or do nothing if we don't have one.
* (action-do-nothing)
* (action-turn direction) -- turn in the given direction



## Data

Some way to dump the results of a battle to JSON or YAML or something so that I can analyze them: [DONE]
* Surviving soldiers on both sides
* Wounded soldiers on both sides
* Number of turns taken
* FIXME: Any other relevant criteria?

Create a battle.cfg file which makes the sides roughly even:
  8 soldiers, laser rifles, personal armour, 1 grenade each, identical medium stats, insane morale
  8 sectoids, heavy plasmas, alien grenades (various ranks? But no leaders), insane morale


## Speed

Need some way to detach it from the animation speed and just draw as fast as the computer can go.
Should also disable sound-playing when this mode is on. (Looks like there's already a `mute` option for that.)

Should be some a command-line option so that I can replay things slowly if I want to see details.


## Miscellaneous

Panicking is an issue — the AI doesn't handle it well. Can we disable panic, or give all units 255 morale?

Opposing force should be aliens that don't have mind control. That wouldn't work well.

Should I disable the "aliens automatically know the location of every enemy unit after 20 turns" behaviour?
  - Not fair
  - But probably would speed things up

Assertion: Bail if an alien starts using a JanetAIModule — something weird happened there. [DONE]

Fix the "random starting number of aliens" behaviour for battles — should always be as many aliens as soldiers.

Let's not have support for kneeling/standing for now. We can think about adding it later.

OpenXcom's AI implementation doesn't yet let the AI pick things up off the ground, but it might be nice to add that
in the future in case we want units to be able to take dead units' grenades or whatever. Very low priority.

## Harness

Ruby? Janet? program to control the genetic aspect.

Directory of battle.cfg files for the various scenarios

SQLite database:
* scenarios
  * battle.cfg filename
  * random seed

* script
  * janet_source
  * generation
  * parent_script_id

* results
  * scenario_id
  * script_id
  * score
  * outcome (win, lose, draw)
  * survivors
  * kills
  * turns_taken

Note, for the scoring, that "draw" is probably a worse outcome than "lose". Probably means that it just sat in one place and didn't do anything.
Seems like promoting draw-prone scripts would be a great way to end up in evolutionary stasis.

When run:

* For each script in the current generation:
  * For each scenario:
    * Write the Janet source to a file
    * Execute `openxcom` with the right parameters to run that scenario with that AI file as fast as possible
    * ...
