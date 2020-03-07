HomingSpawner = {
	fireTime = 400,
	postMoveTime = 10,
	fill = Color.new(0, 128, 0),
	difficulty = 35
}

function HomingSpawner.spawnEnemies(spawner)
	efill = Color.new(0, 128, 0)
	return {
		amount = 1,
		enemies = {
			Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 0.0, 400, efill)
		}
	}
end

function HomingSpawner.enemyUpdate(enemy, environment)
	local diffX = enemy.position.x - environment.player.position.x - 10
	local diffY = enemy.position.y - environment.player.position.y - 10
	local distance = math.sqrt(((enemy.position.x - environment.player.position.x) * (enemy.position.x - environment.player.position.x)) + ((enemy.position.y - environment.player.position.y) * (enemy.position.y - environment.player.position.y)))

	enemy.velocity.x = (-1 / distance) * diffX
	enemy.velocity.y = (-1 / distance) * diffY
end