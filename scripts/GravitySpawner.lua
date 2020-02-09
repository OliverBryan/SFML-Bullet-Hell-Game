GravitySpawner = {
	fireTime = 200,
	postMoveTime = 20,
	fill = Color.new(128, 128, 128),
	postMoveFill = Color.new(47, 79, 79)
}

function GravitySpawner.spawnEnemies(spawner)
	e = Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 2.0, 100000000, Color.new(128, 128, 128, 198))
	e.size.x = 10
	e.size.y = 10
	return {
		amount = 1,
		enemies = {
			e
		}
	}
end

function GravitySpawner.enemyUpdate(enemy, environment)
	if enemy.fill.a < 0 then
		enemy.fill.a = 0
	end
	enemy.fill = Color.new(128, 128, 128, enemy.fill.a)
end