GravitySpawner = {
	fireTime = 200,
	postMoveTime = 20,
	fill = Color.new(128, 128, 128),
	postMoveFill = Color.new(47, 79, 79)
}

GravitySpawner.EnemyInstanceVars = {
	alpha = 198
}

function GravitySpawner.EnemyInstanceVars:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return o
end

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
	enemy.instanceVars.alpha = enemy.instanceVars.alpha - 3
	if enemy.instanceVars.alpha < 0 then
		enemy.instanceVars.alpha = 0
	end
	enemy.fill = Color.new(128, 128, 128, enemy.instanceVars.alpha)
end