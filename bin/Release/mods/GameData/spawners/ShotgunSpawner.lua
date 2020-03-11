ShotgunSpawner = {
	fireTime = 50,
	postMoveTime = 30,
	fill = Color.new(128, 0, 128),
	difficulty = 60
}

function ShotgunSpawner.spawnEnemies(spawner)
	efill = Color.new(128, 0, 128)
	return {
		amount = 3,
		enemies = {
			Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 3.5, 300, efill),
			Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 1.0, 3.0, 300, efill),
			Enemy.new(spawner.position.x + 3, spawner.position.y + 20, -1.0, 3.0, 300, efill)
		}
	}
end