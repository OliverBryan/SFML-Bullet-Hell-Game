RicochetSpawner = {
	fireTime = 100,
	fill = Color.new(255, 215, 0)
}

function RicochetSpawner.spawnEnemies(spawner)
	return {
		amount = 1,
		enemies = {
			Enemy.new(spawner.position.x + 3, spawner.position.y + 20, rand(-5, 5), 3, 275, Color.new(255, 215, 0))
		}
	}
end

function RicochetSpawner.enemyUpdate(enemy, environment)
	if enemy.position.x >= 410 then
		enemy.velocity.x = enemy.velocity.x * -1
	end
	if enemy.position.x <= 20 then
		enemy.velocity.x = enemy.velocity.x * -1
	end
	if enemy.position.y >= 410 then
		enemy.velocity.y = enemy.velocity.y * -1
	end
	if enemy.position.y <= 20 then
		enemy.velocity.y = enemy.velocity.y * -1
	end
end

--[[
function RicochetSpawner.spawnerRender(spawner, window)
	rect = Rect:new(Vec2:new(16, 20))
	setRectPosition(rect, spawner.position.x, spawner.position.y)
	topColor = Color.new(255, 215, 0)
	bottomColor = Color.new(0, 0, 0)
	drawGradient(window, rect, topColor, bottomColor)
end --]]