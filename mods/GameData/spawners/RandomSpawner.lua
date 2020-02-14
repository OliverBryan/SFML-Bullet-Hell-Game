RandomSpawner = {
	fireTime = 400,
	postMoveTime = 60,
	fill = Color.new(0, 250, 154),
	postMoveFill = Color.new(32, 178, 170)
}

RandomSpawner.EnemyInstanceVars = {
	c = 30,
	cl = rand(10, 80)
}

function RandomSpawner.EnemyInstanceVars:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return o
end

function RandomSpawner.spawnEnemies(spawner)
	return {
		amount = 1,
		enemies = {
			Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 2.0, 400, Color.new(0, 250, 154))
		}
	}
end

function RandomSpawner.enemyUpdate(enemy, environment) 
	if enemy.instanceVars.c > enemy.instanceVars.cl then
		enemy.velocity.x = rand(-5, 5)
		enemy.velocity.y = rand(0, 5)
		enemy.instanceVars.c = 0
		enemy.instanceVars.cl = rand(10, 80)
	end

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

	enemy.instanceVars.c = enemy.instanceVars.c + 1
end