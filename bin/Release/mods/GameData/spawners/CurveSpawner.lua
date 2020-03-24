CurveSpawner = {
	fireTime = 100,
	fill = Color.new(250, 154, 14),
	difficulty = 40
}

CurveSpawner.EnemyInstanceVars = {
	x = 0,
	first = true,
	a = 0,
	ps = 0
}

function CurveSpawner.EnemyInstanceVars:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	self.a = rand(10, 100)
	o.ps = 1 / rand(1, 5)
	return o
end

function CurveSpawner.spawnEnemies(spawner)
	return {
		amount = 1,
		enemies = {
			Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, rand(2, 3), 400, Color.new(250, 154, 14))
		}
	}
end

function CurveSpawner.enemyUpdate(enemy, environment)
	if enemy.instanceVars.first then
		enemy.instanceVars.x = enemy.position.x
		local distance = math.min(enemy.position.x - 20, 420 - enemy.position.x)
		if distance > 100 then distance = 100 end
		enemy.instanceVars.a = rand(0, math.floor(distance))
		enemy.instanceVars.first = false
	end

	enemy.position.x = (enemy.instanceVars.a * math.sin((enemy.position.y / 20) * enemy.instanceVars.ps)) + enemy.instanceVars.x
end