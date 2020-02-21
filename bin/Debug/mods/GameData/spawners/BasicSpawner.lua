BasicSpawner = {
	fireTime = 60,
	fill = Color.new(35, 38, 36)
}

function BasicSpawner.spawnEnemies(spawner)
	return {
		amount = 1,
		enemies = {
			Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 2.0, 300, Color.new(35, 38, 36))
		}
	}
end