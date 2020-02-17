ShieldPowerup = {
	sprite = "shield.png",
	activeTime = 600,
	animated = true,
	frames = 11,
	frameDelay = 20
}

function ShieldPowerup.activate(powerup, player)
	player.invincible = true
end

function ShieldPowerup.deactivate(powerup, player)
	player.invincible = false
end

function ShieldPowerup.render(powerup, player, window)
	if powerup.active then
		radius = 20
		circle = Circle.new(radius)
		setCirclePosition(circle, player.position.x - radius + 10, player.position.y - radius + 10)
		circle:setFill(Color.new(255, 255, 255, 0))
		circle:setBorder(Color.new(35, 38, 36))
		circle:setBorderWidth(2)

		draw(window, circle)
	end
end