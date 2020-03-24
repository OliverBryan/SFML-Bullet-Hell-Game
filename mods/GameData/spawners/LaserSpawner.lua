LaserSpawner = {
	fireTime = 300,
	postMoveTime = 60,
	fill = Color.new(255, 0, 0),
	postMoveFill = Color.new(255, 165, 0),
	difficulty = 25,
	stay = true
}

function LaserSpawner.spawnEnemies(spawner)
	e = Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 0.0, 60, Color.new(255, 165, 0))
	e.size.x = 10
	e.size.y = 380
	return {
		amount = 1,
		enemies = {
			e
		}
	}
end