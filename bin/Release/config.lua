-- This file has configurable values for the game

-- Values in the config table can be removed, if not present will be defaulted
config = {
	invincible = false,
	tps = 60,
	cheats = false
}

keybinds = {
	left = {Keys.Left, Keys.A},
	up = {Keys.Up, Keys.W},
	down = {Keys.Down, Keys.S},
	right = {Keys.Right, Keys.D},
	teleport = {Keys.Z, Keys.M},
	powerup = {Keys.X, Keys.N}
}

actions = {
	advance = {
		keys = {{Keys.RShift, Keys.A}, {Keys.LShift, Keys.A}},
		commands = {"set time 0.01", "set position 200 0"}
	},
	accelerate = {
		keys = {{Keys.RShift, Keys.E}},
		commands = {"set invincible true", "set tps 500"}
	},
	decelerate = {
		keys = {{Keys.RShift, Keys.R}},
		commands = {"set invincible false", "set tps 60"}
	},
	invincableon = {
		keys = {{Keys.RShift, Keys.I}},
		commands = {"set invincible true"}
	},
	invincableoff = {
		keys = {{Keys.RShift, Keys.O}},
		commands = {"set invincible false"}
	},
}