SpraySpawner = {
	fireTime = 60,
	fill = Color.new(0, 0, 0),
	difficulty = 50
}

SpraySpawner.SpawnerInstanceVars = {
	ec = 0
}

function SpraySpawner.SpawnerInstanceVars:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return o
end

function SpraySpawner.spawnEnemies(spawner)
	e = Enemy.new(spawner.position.x + 3, spawner.position.y + 20, rand(-3, 3), 3.0, 275, Color.new(0, 0, 0))
	e.size.x = 8
	e.size.y = 8
	return {
		amount = 1,
		enemies = {
			e
		}
	}
end

function SpraySpawner.spawnerUpdate(spawner, environment)
	if not spawner.moving then
		return
	end
	if spawner.instanceVars.ec > 4 then
		e = Enemy.new(spawner.position.x + 3, spawner.position.y + 20, rand(-3, 3), 3.0, 275, Color.new(0, 0, 0))
		e.size.x = 8
		e.size.y = 8
		environment:addEnemy(e, "SpraySpawner")
		spawner.instanceVars.ec = 0
	end
	spawner.instanceVars.ec = spawner.instanceVars.ec + 1
end

function SpraySpawner.spawnerRender(spawner, window)
	rect = Rect:new(Vec2:new(16, 20))
	setRectPosition(rect, spawner.position.x, spawner.position.y)
	topColor = Color.new(0, 0, 255)
	bottomColor = Color.new(255, 215, 0)
	drawGradient(window, rect, topColor, bottomColor)
end

function SpraySpawner.enemyRender(enemy, window)
	rect = Rect:new(Vec2:new(10, 10))
	setRectPosition(rect, enemy.position.x, enemy.position.y)
	topColor = Color.new(0, 0, 255)
	bottomColor = Color.new(255, 215, 0)
	drawGradient(window, rect, topColor, bottomColor)
end