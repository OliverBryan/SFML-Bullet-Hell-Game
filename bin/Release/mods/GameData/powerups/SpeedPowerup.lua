SpeedPowerup = {
	sprite = "speed.png",
	activeTime = 600,
	animated = true,
	frames = 5,
	frameDelay = 4
}

positions = {}

pc = 0
epc = 0

function SpeedPowerup.activate(powerup, player)
	player.speed = 6
end

function SpeedPowerup.deactivate(powerup, player)
	player.speed = 2
	pc = 0
	epc = 0
	positions = {}
end

function SpeedPowerup.render(powerup, player, window)
	if powerup.active then
		for k, v in pairs(positions) do
			rect = Rect.new(Vec2.new(20, 20))
			setRectPosition(rect, v.x, v.y)
			rect:setFill(Color.new(35, 38, 36, v.a))

			draw(window, rect)
		end
	end
end

function SpeedPowerup.update(powerup, player)
	if powerup.active then
		if epc > 2 then
			positions[pc] = {
				x = player.position.x,
				y = player.position.y,
				a = 255
			}
			pc = pc + 1
			epc = 0
		end
		epc = epc + 1

		for k, v in pairs(positions) do
			v.a = v.a - 5
			if v.a < 0 then
				positions[k] = nil
			end
		end
	end
end