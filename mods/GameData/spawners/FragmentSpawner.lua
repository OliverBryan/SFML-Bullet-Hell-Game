FragmentSpawner = {
	fireTime = 150,
	fill = Color.new(222, 5, 78),
	difficulty = 55,
	postMoveTime = 60,
	postMoveFill = Color.new(222, 5, 176)
}

FragmentSpawner.EnemyInstanceVars = {
	time = 0,
	c = 0,
	amnt = rand(1, 4),
	ac = 1
}

function FragmentSpawner.EnemyInstanceVars:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	self.time =  rand(60, 160)
	return o
end

function FragmentSpawner.spawnEnemies(spawner)
	e = Enemy.new(spawner.position.x - 2, spawner.position.y + 20, 0.0, 2.0, 400, Color.new(222, 5, 176))
	e.size.x  = 20
	e.size.y = 20
	return {
		amount = 1,
		enemies = {
			e
		}
	}
end

function FragmentSpawner.enemyUpdate(enemy, environment)
	if enemy.velocity.x ~= 0 then
		return
	end

	enemy.instanceVars.c = enemy.instanceVars.c + 1
	if enemy.instanceVars.c > enemy.instanceVars.time then
		enemy.velocity.y = 0
		amount = rand(2, 8)
		for i = 1, amount do
			local vx = rand(-5, 5)
			while vx == 0 do
				vx = rand(-5, 5)
			end
			environment:addEnemy(Enemy.new(enemy.position.x + 3, enemy.position.y + 20, vx, rand(-5, 5), 400, Color.new(222, 5, 176)), "FragmentSpawner")
		end

		enemy.instanceVars.c = enemy.instanceVars.time - 60
		enemy.instanceVars.ac = enemy.instanceVars.ac + 1

		if enemy.instanceVars.ac > enemy.instanceVars.amnt then
			environment:removeEnemy(enemy)
		end
	end
end