.. Bullet Hell Game documentation master file, created by
   sphinx-quickstart on Mon Feb 10 17:19:13 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. role:: raw-html(raw)
    :format: html

Gameplay Explanation
=============================
Basic Information
.....................
When the game launches, you should see something like this

.. image:: /images/gamestart.png

The black square in the middle of the screen is the player. The black rectangle at the top of the screen is a spawner. The game works by spawning various spawners, which every so often move to a new place and spawn an enemy. The goal of the game is to survive by dodging the enemies. 

.. image:: /images/vocab.png

On the right side of the window is the UI. This shows the time left in the current wave, what wave you are currently on, the amount of teleports and the powerup
that the player has, and other useful information. 

At the end of the wave (when the timer reaches 0), move the player to the top of the screen to begin the next wave. At the end of every wave, a powerup may spawn.
The player may choose to pick up the powerup, or keep their current one. The player can only have one powerup at once. The player's current powerup is indicated next to the teleports. If the powerup is not picked up, it will disappear when the next wave starts. 

The player can also teleport, and can have a total of three teleports at once. When used, they will teleport the player in the same direction that they are moving.
Teleports slowly recharge over time, and the amount of teleports the player currenly has is indicated by the white boxes in the UI. 

Controls
..........
The player movement can be controlled with the traditional WASD keys, or you can use the 4 arrow keys, both do the same thing. You can use the M key or the Z key to teleport. Powerups can be activated with the B key or the C key. 

The reason there are two keys bound for everything is so that two playstyles are support.

Control Scheme 1: :raw-html:`<br />`
Movement: WASD :raw-html:`<br />`
Teleport: M :raw-html:`<br />`
Use Powerup: B :raw-html:`<br />`

Control Scheme 2: :raw-html:`<br />`
Movement: Arrow keys :raw-html:`<br />`
Teleport: Z :raw-html:`<br />`
Use Powerup: B :raw-html:`<br />`

.. toctree::
   :maxdepth: 2
   :caption: Contents: