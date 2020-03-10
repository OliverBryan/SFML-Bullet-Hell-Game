SlowdownPowerup = {
	sprite = "shield.png",
	activeTime = 200,
	animated = true,
	frames = 11,
	frameDelay = 20
}

function SlowdownPowerup.activate(powerup, player, environment)
	environment.tps = 20
	player.speed = 6
end

function SlowdownPowerup.deactivate(powerup, player, environment)
	environment.tps = 60
	player.speed = 2
end