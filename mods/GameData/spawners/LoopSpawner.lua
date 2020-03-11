LoopSpawner = {
	fireTime = 140,
	fill = Color.new(155, 245, 66),
	difficulty = 70
}

function LoopSpawner.spawnEnemies(spawner)
	return {
		amount = 1,
		enemies = {
			Enemy.new(spawner.position.x + 3, spawner.position.y + 20, rand(-5, 5), 3, 275, Color.new(155, 245, 66))
		}
	}
end

function LoopSpawner.enemyUpdate(enemy, environment)
	if enemy.position.x > 410 then
		enemy.position.x = 20
	end
	if enemy.position.x < 20 then
		enemy.position.x = 410
	end
	if enemy.position.y > 410 then
		enemy.position.y = 20
	end
	if enemy.position.y < 20 then
		enemy.position.y = 410
	end
end