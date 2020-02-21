.. Bullet Hell Game documentation master file, created by
   sphinx-quickstart on Mon Feb 10 17:19:13 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. role:: raw-html(raw)
    :format: html

Mod Tutorial
===========================================
This tutorial will go through all the information needed to create a mod, using examples from the spawners that are already in the game, and ends with a complete
example of a modded spawner. 

Keep in mind that all the spawners and powerups currently in the game are part of a mod called GameData, and can be referenced when you want to achieve certain effects or behaviors that are already in the game. Mods in the game are in the Lua scripting language. To create mods, you must have a decent understanding of Lua and how it works, specifically tables
Mods in the game can currently control two types of objects: spawners and powerups.

Mod File Structure
....................
Mods are required to have a certain file structure to them. The name of the mod's main folder must be the mod's name, and inside that folder, there should be one lua file **with the same name as the folder**. This lua file is the mods exports file, where the mod defines all of the spawners and powerups it exports. In that main folder, there can also be several possible subfolders, depending on what type of content your mod exports. If your mod exports spawners, there must be a folder called 'spawners'. If your mod exports powerups, then there must be a folder called 'powerups' and a folder called 'sprites' for powerup sprites. Inside the spawner folder, there should be one lua file for each spawner that the mod exports. **Each spawner lua file must be named the same as you name it in the exports lua file**. The same goes for powerups, each powerup that your mod exports gets its own lua file in the powerups folder. 

For example, the file structure of the 'GameData' mod looks like this

GameData :raw-html:`<br />`
	GameData.lua :raw-html:`<br />`
	spawners :raw-html:`<br />`
		BasicSpawner.lua :raw-html:`<br />`
		GravitySpawner.lua :raw-html:`<br />`
		HomingSpawner.lua :raw-html:`<br />`
		LaserSpawner.lua :raw-html:`<br />`
		LoopSpawner.lua :raw-html:`<br />`
		RandomSpawner.lua :raw-html:`<br />`
		RicochetSpawner.lua :raw-html:`<br />`
		ShotgunSpawner.lua :raw-html:`<br />`
		SpraySpawner.lua :raw-html:`<br />`
		WaveSpawner.lua :raw-html:`<br />`
	powerups :raw-html:`<br />`
		ShieldPowerup.lua :raw-html:`<br />`
	sprites :raw-html:`<br />`
		shield.png :raw-html:`<br />`

The Mod Exports File
.....................
epic

.. toctree::
   :maxdepth: 2
   :caption: Contents: